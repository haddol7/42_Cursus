/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:19 by daeha             #+#    #+#             */
/*   Updated: 2024/08/16 18:36:44 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"
#include "structures.h"
#include "print.h"
#include "utils.h"
#include "scene.h"
#include "trace.h"
#include "libft.h"

t_scene *scene_init(t_mlx engine)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka;

    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        exit(12);
	ft_memset(scene, 0, sizeof(t_scene));
    scene->canvas = canvas(WINDOW_W, WINDOW_H);
    scene->camera = camera(&scene->canvas, engine); 
    //world = object(SP, sphere(point3(0, 0, -2000), 995), color3(1, 1, 1),"./rt/texture/earth_diffuse.xpm", engine.mlx);
    //world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0),"./rt/texture/earth_diffuse.xpm", engine.mlx);
    world = object(SP, sphere(point3(-4, 0, -5), 2), color3(0.5, 0, 0),"./rt/texture/earth_diffuse.xpm", engine.mlx);
    oadd(&world, object(SP, sphere(point3(4, 0, -5), 4), color3(0, 0.5, 0), "CHECKER", engine.mlx));
    oadd(&world, object(SP, sphere(point3(0, 100, -1000), 500), color3(1, 0, 0), NULL, engine.mlx));
    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 0, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0), NULL, engine.mlx);
    //oadd(&lights, object(LIGHT_POINT, light_point(point3(-2, 5, 3), color3(0, 1, 0), 0.5), color3(0, 0, 0), NULL, engine.mlx));
	//oadd(&lights, object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(0, 0, 1), 0.), color3(0, 0, 0), NULL, engine.mlx));
	scene->light = lights;
    ka = 0.1;
    scene->ambient = vmult(color3(1,1,1), ka);
    return (scene);
}

t_mlx	*engine_init(void)
{
	t_mlx	*engine;

	engine = (t_mlx *)malloc(sizeof(t_mlx));
	ft_memset(engine, 0, sizeof(t_mlx));
	engine->img = (t_img *)malloc(sizeof(t_img));
	if (engine == NULL)
		exit(ERR_MLC);
	engine->mlx = mlx_init();
	if (engine->mlx == NULL)
		exit(ERR_MLX);
	engine->win = mlx_new_window(engine->mlx, WINDOW_W, WINDOW_H, "minirt");
	if (engine->win == NULL)
		exit(ERR_MLX);
	engine->img->id = mlx_new_image(engine->mlx, WINDOW_W, WINDOW_H);
	if (engine->img->id == NULL)
		exit(ERR_MLX);
	engine->img->addr = mlx_get_data_addr(engine->img->id, &engine->img->bits_per_pixel, \
										&engine->img->line_size, &engine->img->endian);
	engine->fov = 60;
	return (engine);
}

void	draw_ray(t_scene *scene, t_mlx *engine)
{
	int         i;
    int         j;
    double      u;
    double      v;
    t_color3    pixel_color;

	j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {	
			pixel_color = vec3(0, 0, 0);
			for (int sample = 0; sample < scene->camera.samples_per_pixel; sample++)
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
			}
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
	t_data	*data;
	t_camera *cam;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (keycode == KEY_A)
		data->engine->trans = vplus_(data->engine->trans, -cam->u.x, 0,  -cam->u.z);
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
	*cam = camera(&data->scene->canvas, *data->engine);
	draw_ray(data->scene, data->engine);
	return (0);
}

int	mouse_press_hook(int keycode, int x, int y, void *data_addr)
{
	t_data	*data;

	data = data_addr;
	data->engine->mouse.x = x;
	data->engine->mouse.y = y;
	data->engine->mouse.z = keycode;
	if (keycode == MOUSE_LEFT)
	{
		t_scene		*scene;
		t_object	*selected_obj;
		
		scene = data->scene;
		scene->rec = record_init();
		scene->ray = ray_primary(&scene->camera, ((double)x) / (scene->canvas.width - 1), ((double)y) / (scene->canvas.height - 1));
		selected_obj = hit(scene->world, &scene->ray, &scene->rec);
		if (selected_obj)
		{
			dprintf(2, "OK!\n");
		}
		else
			dprintf(2, "NO!\n");
		scene->selected_obj = selected_obj;
	}
	return (0);
}

int	mouse_drag_hook(int x, int y, void *data_addr)
{
	t_data	*data;
	t_camera *cam;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (data->engine->mouse.z == MOUSE_RIGHT)
	{
		data->engine->rotate.y += ((double)x - data->engine->mouse.x) * 0.01;
		data->engine->rotate.x -= ((double)y - data->engine->mouse.y) * 0.01;
	}
	if (data->engine->rotate.x > 80)
		data->engine->rotate.x = 80;
	else if (data->engine->rotate.x < -80)
		data->engine->rotate.x = -80;
	if (data->engine->rotate.y > 360 || data->engine->rotate.y < -360)
		data->engine->rotate.y = 0;
	*cam = camera(&data->scene->canvas, *data->engine);
	draw_ray(data->scene, data->engine);
	return (0);
}

int	mouse_release_hook(int keycode, int x, int y, void *data_addr)
{	
	t_data	*data;
	t_camera *cam;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (keycode != data->engine->mouse.z)
		return (0);
	if (keycode == MOUSE_LEFT || keycode == MOUSE_RIGHT)
	{
		data->engine->mouse.z = 0;
		// if (keycode == MOUSE_RIGHT)
		// {
		// 	data->map.angular.x += data->map.mouse.x;
		// 	data->map.angular.y += data->map.mouse.y;
		// }
		// else
		// {
		// 	data->map.translate.x += data->map.mouse.x;
		// 	data->map.translate.y += data->map.mouse.y;
		// }
		// data->map.mouse.x = 0;
		// data->map.mouse.y = 0;
	}
	if (x * y == 42)
		printf("\r🥚\r");
	*cam = camera(&data->scene->canvas, *data->engine);
	draw_ray(data->scene, data->engine);
	return (0);
}

int     main(void)
{	
	t_data		data;

	data.engine = engine_init();
   	data.scene = scene_init(*data.engine);
	draw_ray(data.scene, data.engine);
	mlx_hook(data.engine->win, 2, 0, key_hook, &data);
	mlx_hook(data.engine->win, 4, 0, mouse_press_hook, &data);
	mlx_hook(data.engine->win, 5, 0, mouse_release_hook, &data);
	mlx_hook(data.engine->win, 6, 0, mouse_drag_hook, &data);
	mlx_hook(data.engine->win, 17, 0, terminate, &data);
	mlx_loop(data.engine->mlx);
    return (0);
}
