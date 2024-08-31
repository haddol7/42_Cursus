/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_object_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 04:08:59 by daeha             #+#    #+#             */
/*   Updated: 2024/08/31 23:56:22 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_sphere(int keycode, t_data *data)
{
	t_sphere	*sp;

	sp = (t_sphere *)data->scene->selected_obj->element;
	object_translation(keycode, &sp->center, data);
}

void	handle_cylinder(int keycode, t_data *data)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)data->scene->selected_obj->element;
	object_translation(keycode, &cy->center, data);
	object_rotation(keycode, &cy->normal);
}

void	handle_plane(int keycode, t_data *data)
{
	t_plane		*pl;

	pl = (t_plane *)data->scene->selected_obj->element;
	object_translation(keycode, &pl->center, data);
	object_rotation(keycode, &pl->normal);
}

void	handle_cone(int keycode, t_data *data)
{
	t_cone	*co;

	co = (t_cone *)data->scene->selected_obj->element;
	object_translation(keycode, &co->center, data);
	object_rotation(keycode, &co->normalize);
}

void	handle_light(int keycode, t_data *data)
{
	t_light		*light;

	light = (t_light *)data->scene->selected_obj->element;
	if (keycode == KEY_L)
		data->scene->selected_obj = data->scene->selected_obj->next;
	else if (keycode == KEY_DOWN && light->bright_ratio > 0)
		light->bright_ratio -= 0.1;
	else if (keycode == KEY_UP && light->bright_ratio < 1)
		light->bright_ratio += 0.1;
	else
		object_translation(keycode, &light->origin, data);
}

void	handle_camera(int keycode, t_data *data)
{
	t_camera	*cam;
	t_mlx		*engine;	

	cam = &data->scene->camera;
	engine = data->engine;
	if (keycode == KEY_ESC)
		terminate((void *)data);
	else if (keycode == KEY_C && engine->fov > 5)
		engine->fov -= 5;
	else if (keycode == KEY_Z && engine->fov < 175)
		engine->fov += 5;
	else if (keycode == KEY_LEFT && engine->rotate.z < 90)
		engine->rotate.z += 5;
	else if (keycode == KEY_RIGHT && engine->rotate.z > -90)
		engine->rotate.z -= 5;
	else
		object_translation(keycode, &engine->trans, data);
}
