/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_object_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 04:08:59 by daeha             #+#    #+#             */
/*   Updated: 2024/09/02 21:51:45 by jungslee         ###   ########.fr       */
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
