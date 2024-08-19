/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:19 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 18:36:01 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "structures.h"
#include "print.h"
#include "utils.h"
#include "scene.h"
#include "trace.h"
#include "map.h"

//TODO: capital_ob
t_scene	*scene_init(int fd, t_mlx engine)
{
	t_scene	*scene;
	int		capital_ob;

	capital_ob = 0;
	scene = (t_scene *)ft_malloc(sizeof(t_scene));
	scene->canvas = canvas(WINDOW_W, WINDOW_H);
	map_validity(fd, scene, &capital_ob, engine);
	if (capital_ob != 3)
		error_exit("too many capital object");
	return (scene);
}

t_mlx	*engine_init(void)
{
	t_mlx	*engine;

	engine = (t_mlx *)ft_malloc(sizeof(t_mlx));
	engine->mlx = mlx_init();
	if (engine->mlx == NULL)
		exit(ERR_MLX);
	engine->win = mlx_new_window(engine->mlx, WINDOW_W, WINDOW_H, "minirt");
	if (engine->win == NULL)
		exit(ERR_MLX);
	engine->img = (t_img *)ft_malloc(sizeof(t_img));
	engine->img->id = mlx_new_image(engine->mlx, WINDOW_W, WINDOW_H);
	if (engine->img->id == NULL)
		exit(ERR_MLX);
	engine->img->addr = mlx_get_data_addr(engine->img->id, \
						&engine->img->bits_per_pixel, \
						&engine->img->line_size, &engine->img->endian);
	engine->fov = 60;
	return (engine);
}

t_color3	calculate_ray_color(int i, int j, t_scene *scene)
{
	t_color3    pixel_color;
	int			sample;
	double      u;
    double      v;
	
	sample = 0;
	pixel_color = vec3(0, 0, 0);
	while (sample < scene->camera.samples_per_pixel)
	{	
		if (scene->camera.samples_per_pixel > 1)
		{
			u = ((double)i + random_double_(-1, 1)) / (scene->canvas.width - 1);
			v = ((double)j + random_double_(-1, 1)) / (scene->canvas.height - 1);
		}
		else
		{
			u = ((double)i) / (scene->canvas.width - 1);
			v = ((double)j) / (scene->canvas.height - 1);
		}
		scene->ray = ray_primary(&scene->camera, u, v);
		pixel_color = ray_color(scene, pixel_color);
		sample++;
	}
	return (pixel_color);
}

void	draw_ray(t_scene *scene, t_mlx *engine)
{
    t_color3    pixel_color;
	int			step;
	int         i;
    int         j;

	step = scene->canvas.height / 100;
	j = scene->canvas.height - (step / 2);
    while (j >= 0)
    {
        i = step / 2;
        while (i < scene->canvas.width)
        {	
			pixel_color = calculate_ray_color(i, j, scene);
			for (int x = - (step / 2); x < (step / 2); x++)
			{
				for (int y = - (step / 2); y < (step / 2); y++)
            		write_color(engine->img, pixel_color, i + x, scene->canvas.height - 1 - (j + y));
			}
            i += step;
        }
        j -= step;
    }
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, engine->img->id);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->id, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, engine->win);
}


void	draw_ray_high_resolution(t_scene *scene, t_mlx *engine)
{
	t_color3    pixel_color;
	int			i;
    int			j;

	j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {	
			pixel_color = calculate_ray_color(i, j, scene);
            write_color(engine->img, pixel_color, i, scene->canvas.height - 1 - j);
            ++i;
        }
        --j;
    }
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, engine->img->id);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->id, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, engine->win);
}

int	terminate(void *data_addr)
{
	t_data	*data;

	data = (t_data *)data_addr;
	mlx_destroy_image(data->engine->mlx, data->engine->img->id);
	mlx_destroy_window(data->engine->mlx, data->engine->win);
	printf("\033[0;92mProgram closed!\n");
	exit(0);
}

int	key_hook(int keycode, void *data_addr)
{	
	static int	last_keycode = -1;
	t_data		*data;
	t_camera	*cam;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (last_keycode != keycode)
	{
		data->engine->press_count++;
		last_keycode = keycode;
	}
	if (keycode == KEY_A)
		data->engine->trans = vplus_(data->engine->trans, -cam->u.x, 0, -cam->u.z);
	else if (keycode == KEY_D)
		data->engine->trans = vplus_(data->engine->trans, cam->u.x, 0, cam->u.z);
	else if (keycode == KEY_W)
		data->engine->trans = vplus_(data->engine->trans, -cam->w.x, 0, -cam->w.z);
	else if (keycode == KEY_S)
		data->engine->trans = vplus_(data->engine->trans, cam->w.x, 0, cam->w.z);
	else if (keycode == KEY_Q)
		data->engine->trans = vplus_(data->engine->trans, 0, 1, 0);
	else if (keycode == KEY_E)
		data->engine->trans = vplus_(data->engine->trans, 0, -1, 0);
	else if (keycode == KEY_C && data->engine->fov > 5)
		data->engine->fov -= 5;
	else if (keycode == KEY_Z && data->engine->fov < 175)
		data->engine->fov += 5;
	else if (keycode == KEY_LEFT && data->engine->rotate.z < 90)
		data->engine->rotate.z += 5;
	else if (keycode == KEY_RIGHT && data->engine->rotate.z > -90)
		data->engine->rotate.z -= 5;
	else if (keycode == KEY_ESC)
		terminate((void *)data);
	else
		data->engine->press_count--;
	*cam = camera(&data->scene->canvas, *data->engine);
	draw_ray(data->scene, data->engine);
	return (0);
}

int	key_release_hook(int keycode, void *data_addr)
{	
	t_data	*data;
	t_camera *cam;

	keycode = 0;
	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	*cam = camera(&data->scene->canvas, *data->engine);
	if(--data->engine->press_count > 0)
		draw_ray(data->scene, data->engine);
	else
		draw_ray_high_resolution(data->scene, data->engine);
	if (data->engine->press_count < 0)
		data->engine->press_count = 0;
	return (0);
}

int	mouse_press_hook(int keycode, int x, int y, void *data_addr)
{
	t_data		*data;
	t_scene		*scene;
	t_object	*selected_obj;

	data = data_addr;
	data->engine->mouse.x = x;
	data->engine->mouse.y = y;
	data->engine->mouse.z = keycode;
	data->engine->press_count++;
	if (keycode == MOUSE_LEFT)
	{
		scene = data->scene;
		scene->rec = record_init();
		scene->ray = ray_primary(&scene->camera, ((double)x) / (scene->canvas.width - 1), ((double)y) / (scene->canvas.height - 1));
		selected_obj = hit(scene->world, &scene->ray, &scene->rec);
		if (selected_obj)
		{
			dprintf(2, "%f %f OK!\n", ((double)x) / (scene->canvas.width - 1), ((double)y) / (scene->canvas.height - 1));
		}
		else
			dprintf(2, "%f %f NO!\n", ((double)x) / (scene->canvas.width - 1), ((double)y) / (scene->canvas.height - 1));
		scene->selected_obj = selected_obj;
	}
	return (0);
}

int	mouse_drag_hook(int x, int y, void *data_addr)
{
	t_data		*data;
	t_camera	*cam;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (data->engine->mouse.z == MOUSE_RIGHT)
	{
		data->engine->mouse_delta.x = ((double)x - data->engine->mouse.x);
		data->engine->mouse_delta.y = -((double)y - data->engine->mouse.y);
	}
	else
		return (0);
	*cam = camera(&data->scene->canvas, *data->engine);
	draw_ray(data->scene, data->engine);
	return (0);
}

int	mouse_release_hook(int keycode, int x, int y, void *data_addr)
{	
	t_data		*data;
	t_camera	*cam;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (keycode != data->engine->mouse.z)
		return (0);
	if (keycode == MOUSE_RIGHT)
	{
		data->engine->rotate.x += -((double)y - data->engine->mouse.y);
		data->engine->rotate.y += ((double)x - data->engine->mouse.x);
		data->engine->mouse.z = 0;
		data->engine->mouse_delta.x = 0;
		data->engine->mouse_delta.y = 0;
	}
	*cam = camera(&data->scene->canvas, *data->engine);
	if (--data->engine->press_count > 0)
		draw_ray(data->scene, data->engine);
	else
		draw_ray_high_resolution(data->scene, data->engine);
	if (data->engine->press_count < 0)
		data->engine->press_count = 0;
	return (0);
}

int	main(int argc, char *argv[])
{	
	int			fd;
	t_data		data;

	fd = argument_validity(argc, argv[1]);
	data.engine = engine_init();
	data.scene = scene_init(fd, *data.engine);
	draw_ray_high_resolution(data.scene, data.engine);
	mlx_hook(data.engine->win, 2, 0, key_hook, &data);
	mlx_hook(data.engine->win, 3, 0, key_release_hook, &data);
	mlx_hook(data.engine->win, 4, 0, mouse_press_hook, &data);
	mlx_hook(data.engine->win, 5, 0, mouse_release_hook, &data);
	mlx_hook(data.engine->win, 6, 0, mouse_drag_hook, &data);
	mlx_hook(data.engine->win, 17, 0, terminate, &data);
	mlx_loop(data.engine->mlx);
	return (0);
}
