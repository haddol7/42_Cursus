/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_object_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:36:19 by daeha             #+#    #+#             */
/*   Updated: 2024/09/09 21:39:36 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_object	*next_light_obj(t_data *data);

void	object_translation(int keycode, t_vec3 *center, t_data *data)
{
	t_camera	*cam;

	cam = &data->scene->camera;
	if (keycode == KEY_A)
		*center = vplus_(*center, -cam->u.x, 0, -cam->u.z);
	else if (keycode == KEY_D)
		*center = vplus_(*center, cam->u.x, 0, cam->u.z);
	else if (keycode == KEY_W)
		*center = vplus_(*center, -cam->w.x, 0, -cam->w.z);
	else if (keycode == KEY_S)
		*center = vplus_(*center, cam->w.x, 0, cam->w.z);
	else if (keycode == KEY_Q)
		*center = vplus_(*center, 0, 1, 0);
	else if (keycode == KEY_E)
		*center = vplus_(*center, 0, -1, 0);
	else if (keycode == KEY_L)
		data->scene->selected_obj = next_light_obj(data);
	else if (keycode == KEY_ESC)
		data->scene->selected_obj = NULL;
}

void	object_rotation(int keycode, t_vec3 *normal)
{
	if (keycode == KEY_ONE)
		rotation(normal, vec3(0, 1, 0), 5);
	else if (keycode == KEY_TWO)
		rotation(normal, vec3(0, 1, 0), -5);
	else if (keycode == KEY_THREE)
		rotation(normal, vec3(1, 0, 0), 5);
	else if (keycode == KEY_FOUR)
		rotation(normal, vec3(1, 0, 0), -5);
	else if (keycode == KEY_FIVE)
		rotation(normal, vec3(0, 0, 1), 5);
	else if (keycode == KEY_SIX)
		rotation(normal, vec3(0, 0, 1), -5);
}

static t_object	*next_light_obj(t_data *data)
{
	t_object	*obj;

	obj = data->scene->selected_obj;
	if (obj && obj->type == LIGHT)
		return (obj->next);
	else
		return (data->scene->light);
}
