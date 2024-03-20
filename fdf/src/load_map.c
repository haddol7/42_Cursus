/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:08:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/20 22:59:30 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static char	*read_map_as_one_line(int fd);
static void	check_map_size(char *content, t_map *map);
static int	check_map_value(char **content, int *color);
static void	allocate_map(char *content, t_map *map);
static int	check_map_color(char **s);

/*
load_map(char *content, t_map *map)

	call read_map function to read .fdf files.
	
	when a file is given below,
	1	2	3
	4	5	6
	7	8	9
	
	map.point is initialized like
	map.point[0].x = 0 | map.point[0].y = 0 | map.point[0].z = 1
	map.point[1].x = 1 | map.point[1].y = 0 | map.point[1].z = 2
	map.point[2].x = 2 | map.point[2].y = 0 | map.point[2].z = 3
	...

	and map.col and map.row are initialized by 3.

Subject consider all given map files as well formatted. But function should handle
errors

1. system-call function error
2. map file format error
*/

static void	set_scale(t_map *map)
{
	size_t	i;
	size_t	size;
	int		z_max;
	
	i = 0;
	z_max = -2147483648;
	size = map->col * map->row;
	if (map->col > map->row)
		map->scale = WINDOW_X_SIZE / map->col;
	else
		map->scale = WINDOW_Y_SIZE / map->row;
	while (i < size)
	{	
		if (z_max < map->point[i].z)
			z_max = map->point[i].z;
		i++;
	}
	i = 0;
	while (i < size)
	{
		map->point[i].z *= map->scale;
		map->point[i].z /= z_max;
		i++;
	}
}

void	load_map(char *dir, t_client *data)
{
	int		fd;
	char	*content;

	fd = open(dir, O_RDONLY);
	if (fd == -1)
		fdf_error(ERR_OPN);
	content = read_map_as_one_line(fd);
	check_map_size(content, &data->map);
	allocate_map(content, &data->map);
	free(content);
	close(fd);
	set_scale(&data->map);
	draw(data->map, &data->img, data->mlx, data->win);
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
	map->col = 0;
	while (*s != '\0')
	{
		if (*s != ' ' && *s != '\n' && fdf_isspace(*(s + 1)))
			x++;
		if (*s == '\n')
		{
			if ((x != map->col && map->col != 0) || x == 0)
				fdf_error(ERR_M_SIZE);
			if (map->col == 0)
				map->col = x;
			x = 0;
			y++;
		}
		s++;
	}
	map->row = y;
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

static void	allocate_map(char *s, t_map *map)
{
	size_t			size;
	unsigned long	i;

	i = 0;
	size = map->col * map->row;
	map->point = malloc(sizeof(t_point) * size);
	if (!map->point)
		fdf_error(ERR_MLC);
	map->copy = malloc(sizeof(t_point_proj) * size);
	if (!map->copy)
		fdf_error(ERR_MLC);
	while (i < size)
	{
		while (!ft_isdigit(*s) && *s != '-')
		{
			if (!fdf_isspace(*s))
				fdf_error(ERR_M_VAL);
			s++;
		}
		map->point[i].x = i % map->col - map->col / 2;
		map->point[i].y = i / map->col - map->row / 2;
		map->point[i].z = check_map_value(&s, &map->point[i].color);
		i++;
	}
}
