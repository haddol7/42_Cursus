/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:01:19 by daeha             #+#    #+#             */
/*   Updated: 2024/08/21 03:24:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_object(int keycode, t_data *data);

int	key_hook(int keycode, void *data_addr)
{
	t_data		*data;

	data = (t_data *)data_addr;
	handle_object(keycode, data);
	data->scene->camera = camera(data->scene, *data->engine);
	if (keycode == KEY_O)
		draw_ray_orig(data->scene, data->engine);
	else
		draw_ray_chunk(data->scene, data->engine);
	return (0);
}

static void	handle_object(int keycode, t_data *data)
{
	t_object_type	type;

	if (data->scene->selected_obj)
	{
		type = data->scene->selected_obj->type;
		if (type == SP)
			handle_sphere(keycode, data);
		else if (type == CY)
			handle_cylinder(keycode, data);
		else if (type == LIGHT_POINT)
			handle_light(keycode, data);
	}
	else
		handle_camera(keycode, data);
}
