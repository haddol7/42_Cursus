/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:01:15 by daeha             #+#    #+#             */
/*   Updated: 2024/09/07 18:51:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	mouse_press_hook(int keycode, int x, int y, void *data_addr)
{
	t_data		*data;
	t_scene		*scene;
	t_object	*selected_obj;

	data = data_addr;
	data->engine->mouse.x = x;
	data->engine->mouse.y = y;
	data->engine->mouse.z = keycode;
	if (keycode == MOUSE_LEFT)
	{
		scene = data->scene;
		scene->camera = camera(scene, *data->engine);
		scene->rec = record_init();
		scene->ray = ray_primary(&scene->camera, \
					((double)x) / (scene->canvas.w - 1), \
					(scene->canvas.h - (double)y) / (scene->canvas.h - 1));
		selected_obj = hit(scene->world, &scene->ray, &scene->rec);
		scene->selected_obj = selected_obj;
	}
	return (0);
}

int	mouse_drag_hook(int x, int y, void *data_addr)
{
	t_data		*data;
	t_camera	*cam;
	double		temp_y;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (data->engine->mouse.z == MOUSE_RIGHT)
	{
		data->engine->mouse_delta.x = ((double)x - data->engine->mouse.x);
		temp_y = -((double)y - data->engine->mouse.y);
		if (temp_y + data->engine->rotate.x <= 90 && \
			temp_y + data->engine->rotate.x >= -90)
			data->engine->mouse_delta.y = temp_y;
	}
	else
		return (0);
	*cam = camera(data->scene, *data->engine);
	draw_ray_chunk(data->scene, data->engine);
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
		if (data->engine->rotate.x > 90)
			data->engine->rotate.x = 90;
		else if (data->engine->rotate.x < -90)
			data->engine->rotate.x = -90;
		data->engine->rotate.y += ((double)x - data->engine->mouse.x);
		data->engine->mouse.z = 0;
		data->engine->mouse_delta.x = 0;
		data->engine->mouse_delta.y = 0;
	}
	*cam = camera(data->scene, *data->engine);
	draw_ray_chunk(data->scene, data->engine);
	return (0);
}
