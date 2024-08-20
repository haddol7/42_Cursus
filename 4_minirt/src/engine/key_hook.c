/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:01:19 by daeha             #+#    #+#             */
/*   Updated: 2024/08/20 17:42:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (data->scene->selected_obj)
	{	
		t_sphere *test;

		test = (t_sphere *)data->scene->selected_obj->element;
		if (keycode == KEY_A)
			test->center.x -= 1;
		else if (keycode == KEY_D)
			test->center.x += 1;
		else if (keycode == KEY_W)
			test->center.z -= 1;
		else if (keycode == KEY_S)
			test->center.z += 1;
		else if (keycode == KEY_Q)
			test->center.y += 1;
		else if (keycode == KEY_E)
			test->center.y -= 1;
	}
	else
	{
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
	}
	*cam = camera(data->scene, *data->engine);
	draw_ray_chunk(data->scene, data->engine);
	return (0);
}

int	key_release_hook(int keycode, void *data_addr)
{	
	t_data		*data;
	t_camera	*cam;

	keycode = 0;
	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	*cam = camera(data->scene, *data->engine);
	if (--data->engine->press_count > 0)
		draw_ray_chunk(data->scene, data->engine);
	else
		draw_ray_orig(data->scene, data->engine);
	if (data->engine->press_count < 0)
		data->engine->press_count = 0;
	return (0);
}
