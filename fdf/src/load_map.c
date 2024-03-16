/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:08:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/15 20:35:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static char	*read_map_as_one_line(int fd);
static void	check_map_size(char *content, t_map *map);
static int	check_map_value(char **content, int *color);
static void	transform_map(char *content, t_map *map);
static int	check_map_color(char **s);

/*
load_map(char *content, t_map *map)

	call read_map function to read .fdf files.
	
	when a file is given below,
	1	2	3
	4	5	6
	7	8	9
	
	map.data is initialized like
	map.data[0].x = 0 | map.data[0].y = 0 | map.data[0].z = 1
	map.data[1].x = 1 | map.data[1].y = 0 | map.data[1].z = 2
	map.data[2].x = 2 | map.data[2].y = 0 | map.data[2].z = 3
	...

	and map.x_size and map.y_size are initialized by 3.

Subject consider all given map files as well formatted. But function should handle
errors

1. system-call function error
2. map file format error
*/

void	load_map(char *dir, t_map *map)
{
	int		fd;
	char	*content;

	fd = open(dir, O_RDONLY);
	if (fd == -1)
		fdf_error(ERR_OPN);
	content = read_map_as_one_line(fd);
	check_map_size(content, map);
	transform_map(content, map);
	free(content);
	close(fd);
}

//WARNING : FDF_BUFFER_SIZE must not exceed size of stack of memory
static char	*read_map_as_one_line(int fd)
{
	int		read_size;
	char	buffer[FDF_BUFFER_SIZE];
	char	*temp;
	char	*res;

	temp = ft_strdup("");
	res = temp;
	if (temp == NULL)
		fdf_error(ERR_MLC);
	read_size = read(fd, buffer, FDF_BUFFER_SIZE);
	while (read_size != 0)
	{
		if (read_size == -1)
			fdf_error(ERR_RD);
		buffer[read_size] = '\0';
		res = ft_strjoin(temp, buffer);
		if (res == NULL)
			fdf_error(ERR_MLC);
		free(temp);
		temp = res;
		read_size = read(fd, buffer, FDF_BUFFER_SIZE);
	}
	return (res);
}

static void	check_map_size(char *s, t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	map->x_size = 0;
	while (*s != '\0')
	{
		if (*s != ' ' && *s != '\n' && fdf_isspace(*(s + 1)))
			x++;
		if (*s == '\n')
		{
			if ((x != map->x_size && map->x_size != 0) || x == 0)
				fdf_error(ERR_M_SIZE);
			if (map->x_size == 0)
				map->x_size = x;
			x = 0;
			y++;
		}
		s++;
	}
	map->y_size = y;
}

static int	check_map_value(char **s, int *color)
{
	int				sign;
	long			res;
	int				i;

	i = 0;
	res = 0;
	sign = 1;
	if (**s == '-' || **s == ' ')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	while (ft_isdigit(**s))
	{
		res *= 10;
		res += (**s) - '0';
		(*s)++;
	}
	*color = 0xffffff;
	if (!ft_strncmp(*s, ",0x", 3) || !ft_strncmp(*s, ",0X", 3))
		*color = check_map_color(s);
	else if (!fdf_isspace(**s))
		fdf_error(ERR_M_VAL);
	return (res * sign);
}

static int	check_map_color(char **s)
{
	size_t	i;
	int		color;

	color = 0x0;
	*s += 3;
	while (ft_isdigit(**s) || \
	(**s >= 'A' && **s <= 'F') || (**s >= 'a' && **s <= 'f'))
	{
		i = 0;
		if (**s >= 'a' && **s <= 'f')
			i = 10 + **s - 'a';
		else if (**s >= 'A' && **s <= 'F')
			i = 10 + **s - 'A';
		else
			i = **s - '0';
		color *= 16;
		color += i;
		(*s)++;
	}
	if (!fdf_isspace(**s))
		fdf_error(ERR_M_VAL);
	if (color == 0x0)
		return (0xffffff);
	return (color);
}

static void	transform_map(char *s, t_map *map)
{
	size_t			size;
	unsigned long	i;

	i = 0;
	size = map->x_size * map->y_size;
	map->data = malloc(sizeof(t_point) * (size));
	if (map->data == NULL)
		fdf_error(ERR_MLC);
	while (i < size)
	{
		while (!ft_isdigit(*s) && *s != '-')
		{
			if (!fdf_isspace(*s))
				fdf_error(ERR_M_VAL);
			s++;
		}
		map->data[i].x = i % map->y_size;
		map->data[i].y = i / map->y_size;
		map->data[i].z = check_map_value(&s, &map->data[i].color);
		i++;
	}
}
/*
int main(int argc, char **argv)
{
	t_map	map;
	size_t		i;
	
	if (argc != 2)
		return (0);
	
	load_map(argv[1], &map);
	i = 0;
	
	for (size_t y = 0; y < map.y_size; y++)
	{
		for (size_t x = 0; x < map.x_size; x++)
		{
			ft_printf("%d ", map.data[i].z);
			i++;
		}
		ft_printf("\n");
	}
	free(map.data);
}
*/
