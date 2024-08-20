/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:53:25 by daeha             #+#    #+#             */
/*   Updated: 2024/08/21 01:00:46 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color3	calculate_ray_color(int i, int j, t_scene *scene);
static void		write_color_chunk(t_vec3 c, t_color3 p, t_scene *s, t_mlx *mlx);
static void		write_selection_mode(t_scene *scene, t_mlx *engine);

void	draw_ray_chunk(t_scene *scene, t_mlx *engine)
{
	t_color3	pixel_color;
	int			chunk_size;
	int			i;
	int			j;

	chunk_size = scene->canvas.h / CHUNK_DIV;
	j = scene->canvas.h - (chunk_size / 2);
	while (j >= 0)
	{
		i = chunk_size / 2;
		while (i < scene->canvas.w)
		{
			pixel_color = calculate_ray_color(i, j, scene);
			write_color_chunk(vec3(i, j, 0), pixel_color, scene, engine);
			i += chunk_size;
		}
		j -= chunk_size;
	}
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, engine->img->id);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->id, 0, 0);
	write_selection_mode(scene, engine);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, engine->win);
}

void	draw_ray_orig(t_scene *scene, t_mlx *engine)
{
	t_color3	pixel_color;
	int			i;
	int			j;

	j = scene->canvas.h - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.w)
		{
			pixel_color = calculate_ray_color(i, j, scene);
			write_color(engine->img, pixel_color, i, scene->canvas.h - 1 - j);
			++i;
		}
		--j;
	}
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, engine->img->id);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->id, 0, 0);
	write_selection_mode(scene, engine);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, engine->win);
}

static t_color3	calculate_ray_color(int i, int j, t_scene *scene)
{
	t_color3	pixel_color;
	int			sample;
	double		u;
	double		v;

	sample = 0;
	pixel_color = vec3(0, 0, 0);
	while (sample < scene->camera.samples_per_pixel)
	{	
		if (scene->camera.samples_per_pixel > 1)
		{
			u = ((double)i + drandom_(-1, 1)) / (scene->canvas.w - 1);
			v = ((double)j + drandom_(-1, 1)) / (scene->canvas.h - 1);
		}
		else
		{
			u = ((double)i) / (scene->canvas.w - 1);
			v = ((double)j) / (scene->canvas.h - 1);
		}
		scene->ray = ray_primary(&scene->camera, u, v);
		pixel_color = ray_color(scene, pixel_color);
		sample++;
	}
	return (pixel_color);
}

static void	write_color_chunk(t_vec3 c, t_color3 p, t_scene *s, t_mlx *mlx)
{
	int	step;
	int	x;
	int	y;

	step = s->canvas.h / 100;
	x = - (step / 2);
	while (x < (step / 2))
	{
		y = - (step / 2);
		while (y < (step / 2))
		{
			write_color(mlx->img, p, c.x + x, s->canvas.h - 1 - (c.y + y));
			y++;
		}
		x++;
	}
}

static void	write_selection_mode(t_scene *scene, t_mlx *eng)
{
	if (scene->selected_obj && scene->selected_obj->type == LIGHT_POINT)
		mlx_string_put(eng->mlx, eng->win, 5, 20, 0xff00ff, "MODE : LIGHT");
	else if (scene->selected_obj)
		mlx_string_put(eng->mlx, eng->win, 5, 20, 0x00ffff, "MODE : OBJECT");
	else
		mlx_string_put(eng->mlx, eng->win, 5, 20, 0xffff00, "MODE : CAMERA");
}
