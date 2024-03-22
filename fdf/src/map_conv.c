/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 15:52:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_yaw(t_proj *copy, int deg, size_t size);
static void	rotate_pitch(t_proj *copy, int deg, size_t size);
static void	rotate_roll(t_proj *copy, int deg, size_t size);

void	rotate(t_map *map, size_t size)
{
	rotate_roll(map->copy, map->angular.y, size);
	rotate_pitch(map->copy, map->angular.x, size);
	rotate_yaw(map->copy, map->angular.z, size);
}

void	translate(t_proj *point, t_point trans, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		point[i].x_proj += trans.x;
		point[i].y_proj += trans.y;
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
