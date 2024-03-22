/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:28:15 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 20:42:43 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clean_img(t_img *img);
static void	draw_wireframe(t_map map, t_img *img);
static void	copy_scale(t_point *point, t_proj *copy, double scale, size_t size);
static void	isometric_projection(t_proj *copy, size_t size);

void	draw(t_map map, t_img *img, void *mlx, void *win)
{
	size_t	size;

	size = map.row * map.col;
	clean_img(img);
	copy_scale(map.point, map.copy, map.scale, size);
	rotate(&map, size);
	isometric_projection(map.copy, size);
	translate(&map, size);
	draw_wireframe(map, img);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, img->id);
	mlx_put_image_to_window(mlx, win, img->id, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, win);
}

static void	clean_img(t_img *img)
{
	size_t	i;
	int		*img_addr;

	i = 0;
	img_addr = (int *)img->addr;
	while (i < WINDOW_X_SIZE * WINDOW_Y_SIZE)
	{
		img_addr[i] = 0x00;
		i++;
	}
}

static void	draw_wireframe(t_map map, t_img *img)
{
	size_t	i;
	size_t	row;
	size_t	col;

	i = 0;
	row = 0;
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
}

static void	copy_scale(t_point *point, t_proj *copy, double scale, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		copy[i].x = point[i].x * scale;
		copy[i].y = point[i].y * scale;
		copy[i].z = point[i].z * scale;
		copy[i].color = point[i].color;
		i++;
	}
}

static void	isometric_projection(t_proj *copy, size_t size)
{
	size_t	i;
	double	cosine;
	double	sine;

	i = 0;
	cosine = cos(30 * (3.141592) / 180);
	sine = sin(30 * (3.141592) / 180);
	while (i < size)
	{
		copy[i].x_proj = copy[i].x * cosine - copy[i].y * cosine;
		copy[i].y_proj = copy[i].x * sine + copy[i].y * sine - copy[i].z;
		copy[i].x_proj += WINDOW_X_SIZE / 2;
		copy[i].y_proj += WINDOW_Y_SIZE / 2;
		i++;
	}
}
