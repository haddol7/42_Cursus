/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 18:55:40 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_yaw(t_proj *copy, int deg, size_t size);
static void	rotate_pitch(t_proj *copy, int deg, size_t size);
static void	rotate_roll(t_proj *copy, int deg, size_t size);

void	rotate(t_map *map, size_t size)
{
	int	angle_x;
	int	angle_y;

	if (map->mouse_info == 1)
	{
		angle_x = map->angular.x + map->mouse_x;
		angle_y = map->angular.y + map->mouse_y;
	}
	else
	{
		angle_x = map->angular.x;
		angle_y = map->angular.y;
	}
	rotate_pitch(map->copy, angle_x, size);
	rotate_roll(map->copy, angle_y, size);
	rotate_yaw(map->copy, map->angular.z, size);
}

void	translate(t_map *map, size_t size)
{
	size_t	i;
	int		translate_x;
	int		translate_y;

	i = 0;
	if (map->mouse_info == 2)
	{
		translate_x = map->translate.x + map->mouse_x;
		translate_y = map->translate.y + map->mouse_y;
	}
	else
	{
		translate_x = map->translate.x;
		translate_y = map->translate.y;
	}
	while (i < size)
	{
		map->copy[i].x_proj += translate_x;
		map->copy[i].y_proj += translate_y;
		i++;
	}
}

static void	rotate_yaw(t_proj *copy, int deg, size_t size)
{
	size_t	i;
	double	cosine;
	double	sine;
	int		temp_x;
	int		temp_y;

	i = 0;
	cosine = cos(deg * (3.141592) / 180);
	sine = sin(deg * (3.141592) / 180);
	while (i < size)
	{
		temp_x = copy[i].x;
		temp_y = copy[i].y;
		copy[i].x = temp_x * cosine + temp_y * sine;
		copy[i].y = -temp_x * sine + temp_y * cosine;
		i++;
	}
}

static void	rotate_pitch(t_proj *copy, int deg, size_t size)
{
	size_t	i;
	double	cosine;
	double	sine;
	int		temp_y;
	int		temp_z;

	i = 0;
	cosine = cos(deg * (3.141592) / 180);
	sine = sin(deg * (3.141592) / 180);
	while (i < size)
	{	
		temp_y = copy[i].y;
		temp_z = copy[i].z;
		copy[i].y = temp_y * cosine + temp_z * sine;
		copy[i].z = -temp_y * sine + temp_z * cosine;
		i++;
	}
}

static void	rotate_roll(t_proj *copy, int deg, size_t size)
{
	size_t	i;
	double	cosine;
	double	sine;
	int		temp_x;
	int		temp_z;

	i = 0;
	cosine = cos(deg * (3.141592) / 180);
	sine = sin(deg * (3.141592) / 180);
	while (i < size)
	{
		temp_x = copy[i].x;
		temp_z = copy[i].z;
		copy[i].x = temp_x * cosine - temp_z * sine;
		copy[i].z = temp_x * sine + temp_z * cosine;
		i++;
	}
}
