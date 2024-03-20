/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:28:15 by daeha             #+#    #+#             */
/*   Updated: 2024/03/20 23:05:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_line
{
	int	slope;
	int	sign;
	int	step;
}	 t_line;

int get_red(int color)
{
	return ((color & 0xff0000) >> 16);
}
int get_green(int color)
{
	return ((color & 0x00ff00) >> 8);
}
int get_blue(int color)
{
	return (color & 0x0000ff);
}

int	get_color(double *color, int s_color, int i)
{
	int r;
	int g;
	int b;

	r = get_red(s_color);
	g = get_green(s_color);
	b = get_blue(s_color);
	s_color = ((int)(r + i * color[0]) << 16) | ((int)(g + i * color[1]) << 8) | (int)(b + i * color[2]);
	return (s_color);
}

static void pixel_put_to_image(t_img *img, int x_proj, int y_proj, int color)
{
	void	*img_addr;
	
	if (x_proj < 0 || y_proj < 0 || x_proj + 1 > WINDOW_X_SIZE || y_proj + 1 > WINDOW_Y_SIZE)
		return ;

	img_addr = img->addr + img->bits_per_pixel / 8 * x_proj + img->line_size * y_proj;
	*(unsigned int *)img_addr = color;
}

static int set_color(double *color, t_point_proj first, t_point_proj last)
{
	double step;

	if (abs(last.x_proj - first.x_proj) > abs(last.y_proj - first.y_proj))
		step = abs(last.x_proj - first.x_proj);
	else
		step = abs(last.y_proj - first.y_proj);
	color[0] = (get_red(last.color) - get_red(first.color)) / step;
	color[1] = (get_green(last.color) - get_green(first.color)) / step;
	color[2] = (get_blue(last.color) - get_blue(first.color)) / step;
	return (first.color);
}

static void swap_point(t_point_proj *first, t_point_proj *last)
{
	fdf_swap(&first->x_proj, &last->x_proj);
	fdf_swap(&first->y_proj, &last->y_proj);
	fdf_swap(&first->color, &last->color);
}
static void	init_line_info(t_point_proj *first, t_point_proj *last, t_line *l, double *color)
{
	l->step = 0;
	l->slope = 0;
	l->sign = 1;
	if (first->x_proj > last->x_proj)
		swap_point(first, last);
	if (first->y_proj > last->y_proj)
		l->sign = -1;
	if (abs(last->y_proj - first->y_proj) > last->x_proj - first->x_proj)
	{
		l->slope = 1;
		fdf_swap(&first->x_proj, &first->y_proj);
		fdf_swap(&last->x_proj, &last->y_proj);
		if (first->x_proj > last->x_proj)
			swap_point(first, last);
	}
	first->color = set_color(color, *first, *last);
}

static void	put_line_to_image(t_img *img, t_point_proj first, t_point_proj last)
{
	t_line	l;
	double	color[3];
	int	dx;
	int	dy;
	int	p;

	init_line_info(&first, &last, &l, color);
	dx = last.x_proj - first.x_proj;
	dy = (last.y_proj - first.y_proj) * l.sign;
	p = 2 * dy - dx;
	while (first.x_proj <= last.x_proj)
	{
		if (l.slope == 0)
			pixel_put_to_image(img, first.x_proj, first.y_proj, get_color(color, first.color, ++l.step));
		else
			pixel_put_to_image(img, first.y_proj, first.x_proj, get_color(color, first.color, ++l.step));
		if (p >= 0)
		{
			p += 2 * (dy - dx);
			first.y_proj += 1 * l.sign;
		}
		else
			p += 2 * dy;
		first.x_proj++;
	}
}

static void draw_wireframe(t_map map, t_img *img)
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

void translate(t_point_proj *point, t_point trans, size_t size)
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

void scale(t_point_proj *point, int scale, size_t size)
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

static void rotate_yaw(t_point_proj *copy, int deg, size_t size)
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

static void rotate_pitch(t_point_proj *copy, int deg, size_t size)
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

static void rotate_roll(t_point_proj *copy, int deg, size_t size)
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

void rotate(t_map *map, size_t size)
{
	rotate_roll(map->copy, map->angular.y, size);
	rotate_pitch(map->copy, map->angular.x, size);
	rotate_yaw(map->copy, map->angular.z, size);
}


static void map_copy(t_point *point, t_point_proj *copy, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		copy[i].x = point[i].x;
		copy[i].y = point[i].y;
		copy[i].z = point[i].z;
		copy[i].color = point[i].color;		
		i++;
	}
}

static void	clean_img(t_img *img)
{
	int *img_addr;

	img_addr = (int *)img->addr;
	for (int i = 0; i < WINDOW_X_SIZE * WINDOW_Y_SIZE; i++)
		img_addr[i] = 0x00;
}

static void isometric_projection(t_point_proj *copy, size_t size)
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

// static void	draw_gui(t_map map, t_img *img)
// {
	
// }


void draw(t_map map, t_img *img, void *mlx, void *win)
{
	size_t	size;
	
	size = map.row * map.col;
	clean_img(img);
	map_copy(map.point, map.copy, size);
	scale(map.copy, map.scale, size);
	rotate(&map, size);
	isometric_projection(map.copy, size);
	translate(map.copy, map.translate, size);
	draw_wireframe(map, img);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, img->id);
	mlx_put_image_to_window(mlx, win, img->id, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, win);
//	draw_gui(map, img, win);
}
