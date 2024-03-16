/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:28:15 by daeha             #+#    #+#             */
/*   Updated: 2024/03/16 20:23:25 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void pixel_put_to_image(t_img *img, int x_proj, int y_proj, int color)
{
	void	*img_addr;
	
	if (x_proj < 0 || y_proj < 0 || x_proj + 1 > WINDOW_X_SIZE || y_proj + 1 > WINDOW_Y_SIZE)
		return ;

	img_addr = img->addr + img->bits_per_pixel / 8 * x_proj + img->line_size * y_proj;
	*(unsigned int *)img_addr = color;
}

static int is_slope_bigger_than_one(t_point *first, t_point *last, int *minus)
{
	int	dx;
	int	dy;

	dx = first->x_proj - last->x_proj;
	dy = first->y_proj - last->y_proj;
	*minus = 1;
	if (dx * dy < 0)
		*minus = -1;
	if (abs(dy) > abs(dx))
	{
		fdf_swap(&first->x_proj, &first->y_proj);
		fdf_swap(&last->x_proj, &last->y_proj);
		if (*minus == -1)
		{
			fdf_swap(&first->x_proj, &last->x_proj);
			fdf_swap(&first->y_proj, &last->y_proj);
		}
		return (1);
	}
	return (0);
}

static void	put_line_to_image(t_img *img, t_point first, t_point last)
{
	int	dx;
	int	dy;
	int	is_swap;
	int	p;
	int	minus;

	is_swap = is_slope_bigger_than_one(&first, &last, &minus);
	dx = abs(first.x_proj - last.x_proj);
	dy = abs(first.y_proj - last.y_proj);
	p = (2 * dy - dx) * minus;
	if (first.x_proj >= last.x_proj)
	{
		fdf_swap(&first.x_proj, &last.x_proj);
		fdf_swap(&first.y_proj, &last.y_proj);
	}
	while (first.x_proj++ < last.x_proj)
	{
		if (is_swap)
			pixel_put_to_image(img, first.y_proj, first.x_proj, 0xffffff);
		else
			pixel_put_to_image(img, first.x_proj, first.y_proj, 0xffffff);
		if (p * minus >= 0)
		{
			p += (2 * dy - 2 * dx) * minus;
			first.y_proj += 1 * minus;
		}
		else
			p += 2 * dy * minus;
	}
}

void translate(t_point *point, int trans, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		point[i].x += trans;
		point[i].y += trans;
		point[i].z += trans;
		i++;
	}
}

void scale(t_point *point, int scale, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		point[i].x *= scale;
		point[i].y *= scale;
		point[i].z *= scale;
		i++;
	}
}

void rotate_yaw(t_point *point, t_point *copy, int z, size_t size)
{
	size_t	i;
	double	rad;

	rad = z * 3.141592 / 180;
	i = 0;
	while (i < size)
	{
		copy[i].x = point[i].x * cos(rad) + point[i].y * sin(rad);
		copy[i].y = -point[i].x * sin(rad) + point[i].y * cos(rad);
		copy[i].z = point[i].z;
		i++;
	}
}

void rotate_pitch(t_point *point, t_point *copy, int x, size_t size)
{
	size_t	i;
	double	rad;

	rad = x * (3.141592) / 180;
	i = 0;
	while (i < size)
	{
		copy[i].x = point[i].x;
		copy[i].y = point[i].y * cos(rad) + point[i].z * sin(rad);
		copy[i].z = -point[i].y * sin(rad) + point[i].z * cos(rad);
		i++;
	}
}

void rotate_roll(t_point *point, t_point *copy, int y, size_t size)
{
	size_t	i;
	double	rad;

	rad = y * (3.141592) / 180;
	i = 0;
	while (i < size)
	{
		copy[i].x = point[i].x * cos(rad) - point[i].z * sin(rad);
		copy[i].y = point[i].y;
		copy[i].z = point[i].x * sin(rad) + point[i].z * cos(rad);
		i++;
	}
}

void isometric_proj(t_point *copy, size_t size)
{
	size_t	i;
	double	rad;

	i = 0;
	rad = 30 * (3.141592) / 180;
	while (i < size)
	{
		copy[i].x_proj = copy[i].x * cos(rad) - copy[i].y * cos(rad);
		copy[i].y_proj = copy[i].x * sin(rad) + copy[i].y * sin(rad) - copy[i].z;
		copy[i].x_proj += WINDOW_X_SIZE / 2;
		copy[i].y_proj += WINDOW_Y_SIZE / 2;
		i++;
	}
}


void draw(t_map map, t_img *img, void *mlx, void *win)
{
	size_t	size;
	size_t	col;
	size_t	row;
	size_t	i;

	i = 0;
	row = 0;
	size = map.row * map.col;

	rotate_pitch(map.point, map.copy, map.translate.z, size);
//	rotate_yaw(map.point, map.copy, map.translate.z, size);
//	rotate_roll(map.point, map.copy, 180, size);
	isometric_proj(map.copy, size);
	
	while (row < map.row)
	{
		col = 0;
		while (col < map.col)
		{
			if (col + 1 < map.col)
				put_line_to_image(img, map.copy[i], map.copy[i + 1]);
			if (row + 1 < map.row)
				put_line_to_image(img, map.copy[i], map.copy[i + map.col]);
			i++;
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(mlx, win, img->id, 0, 0);
}
