/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:08:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/10 23:37:39 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

void	check_leaks(void)
{
	system("leaks fdf");
}

static char	*read_map_as_one_line(int fd);
static void	check_map_size(char *content, t_map *map);
static int	check_map_value(char **content, int *color);
static void	transform_map(char *content, t_map *map);
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
	content = read_map_as_one_line(fd);
	check_map_size(content, map);
	transform_map(content, map); 
	
	free(content);
	close(fd);
}

static char	*read_map_as_one_line(int fd)
{
	int		read_size;
	char	buffer[FDF_BUFFER_SIZE];
	char	*temp;
	char	*res;

	temp = ft_strdup("");
	read_size = read(fd, buffer, FDF_BUFFER_SIZE);
	while (read_size != 0)
	{
		buffer[read_size] = '\0';
		res = ft_strjoin(temp, buffer);
		free(temp);
		temp = res;
		read_size = read(fd, buffer, FDF_BUFFER_SIZE);
	}
	return (res);
}

static void	check_map_size(char *content, t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	map->x_size = 0;
	while (*content != '\0')
	{
		if (*content != ' ' && *content != '\n' && (*(content + 1) == ' ' || \
											*(content + 1) == '\n' || \
											*(content + 1) == '\0'))
			x++;
		if (*content == '\n')
		{
			if (x != map->x_size && map->x_size != 0)
				ft_printf("format_error\n");
			if (map->x_size == 0)
				map->x_size = x;
			x = 0;
			y++;
		}
		content++;
	}
	map->y_size = y;
}

static int	check_map_value(char **content, int *color)
{
	long			z;
	const	char	*hex;
	int				sign;
	int				i;

	i = 0;
	hex = "0123456789ABCDEF";
	z = 0;
	sign = 1;
	if (**content == '-')
	{
		sign = -1;
		(*content)++;
	}
	while (ft_isdigit(**content))
	{
		z *= 10;
		z += (**content) - '0';
		(*content)++;
	}
	*color = 0xffffff;
	if (ft_strncmp(*content, ",0x", 3) == 0)
	{
		*color = 0;
		*content += 3;
		while (ft_isdigit(**content) || (**content >= 'A' && **content <= 'F'))
		{
			i = 0;
			while (hex[i] != **content)
				i++;
			*color *= 16;
			*color += i;
			(*content)++;
		}
	}
	return (z * sign);
}

static void	transform_map(char *content, t_map *map)
{
	unsigned long long	size;
	unsigned long long	i;

	i = 0;
	size = map->x_size * map->y_size;
	map->data = malloc(sizeof(t_point) * (size));
	while (i < size)
	{
		while (!ft_isdigit(*content) && *content != '-')
			content++;
		map->data[i].x = i % map->y_size;
		map->data[i].y = i / map->y_size;
		map->data[i].z = check_map_value(&content, &map->data[i].color);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_map	map;
	size_t		i;
	
	if (argc != 2)
		return (0);
	load_map(argv[1], &map);
	i = 0;

	ft_printf("==========\n%s=========\n",read_map_as_one_line(open((argv[1]), O_RDONLY)));
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
//	atexit(check_leaks);
}
