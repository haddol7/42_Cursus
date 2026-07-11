/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:08:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/24 19:51:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static char	*read_map_as_one_line(int fd);
static void	check_map_size(char *content, t_map *map);
static void	allocate_map(char *content, t_map *map);
static void	limit_z_value(t_map *map);

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
	set_default_scale(&data->map);
	limit_z_value(&data->map);
	draw(data->map, &data->img, data->mlx, data->win);
	free(content);
}

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
	close(fd);
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
	if (map->row * map->col == 0)
		fdf_error(ERR_M_EMPT);
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
	map->copy = malloc(sizeof(t_proj) * size);
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

static void	limit_z_value(t_map *map)
{
	long long	i;
	long long	size;
	double		z_min;
	double		z_max;

	i = -1;
	size = map->col * map->row;
	z_max = 1;
	z_min = -1;
	while (++i < size)
	{	
		if (z_max < map->point[i].z)
			z_max = map->point[i].z;
		else if (z_min > map->point[i].z)
			z_min = map->point[i].z;
	}
	while (--i >= 0)
	{
		if (map->point[i].z >= 0 && z_max > Z_MAX_VAL)
			map->point[i].z *= Z_MAX_VAL / z_max;
		else if (map->point[i].z < 0 && z_min < Z_MIN_VAL)
			map->point[i].z *= Z_MIN_VAL / z_min;
		if (map->point[i].color == COLOR_NONE)
			set_default_color(&map->point[i].color, map->point[i].z);
	}
}
