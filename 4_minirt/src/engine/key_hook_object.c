/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:36:19 by daeha             #+#    #+#             */
/*   Updated: 2024/08/24 21:44:56 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_camera_i_hate_norm(int keycode, t_data *data);

void	handle_sphere(int keycode, t_data *data)
{
	t_sphere	*sp;
	t_camera	*cam;

	cam = &data->scene->camera;
	sp = (t_sphere *)data->scene->selected_obj->element;
	if (keycode == KEY_A)
		sp->center = vplus_(sp->center, -cam->u.x, 0, -cam->u.z);
	else if (keycode == KEY_D)
		sp->center = vplus_(sp->center, cam->u.x, 0, cam->u.z);
	else if (keycode == KEY_W)
		sp->center = vplus_(sp->center, -cam->w.x, 0, -cam->w.z);
	else if (keycode == KEY_S)
		sp->center = vplus_(sp->center, cam->w.x, 0, cam->w.z);
	else if (keycode == KEY_Q)
		sp->center = vplus_(sp->center, 0, 1, 0);
	else if (keycode == KEY_E)
		sp->center = vplus_(sp->center, 0, -1, 0);
	else if (keycode == KEY_ESC)
		data->scene->selected_obj = NULL;
	else if (keycode == KEY_L)
		data->scene->selected_obj = data->scene->light;
}

// void	debug(char *str, t_vec3 vec)
// {
// 	dprintf(2, "%s -> %f %f %f\n", str, vec.x, vec.y, vec.z);
// }

void	handle_light(int keycode, t_data *data)
{
	t_camera	*cam;
	t_light		*light;

	cam = &data->scene->camera;
	light = (t_light *)data->scene->selected_obj->element;
	if (keycode == KEY_A)
		light->origin = vplus_(light->origin, -cam->u.x, 0, -cam->u.z);
	else if (keycode == KEY_D)
		light->origin = vplus_(light->origin, cam->u.x, 0, cam->u.z);
	else if (keycode == KEY_W)
		light->origin = vplus_(light->origin, -cam->w.x, 0, -cam->w.z);
	else if (keycode == KEY_S)
		light->origin = vplus_(light->origin, cam->w.x, 0, cam->w.z);
	else if (keycode == KEY_Q)
		light->origin = vplus_(light->origin, 0, 1, 0);
	else if (keycode == KEY_E)
		light->origin = vplus_(light->origin, 0, -1, 0);
	else if (keycode == KEY_DOWN && light->bright_ratio > 0)
		light->bright_ratio -= 0.1;
	else if (keycode == KEY_UP && light->bright_ratio < 1)
		light->bright_ratio += 0.1;
	else if (keycode == KEY_ESC)
		data->scene->selected_obj = NULL;
	// debug("light dir -> ", vminus(light->origin, data->scene->rec.p));
	// debug("rec normal -> ", data->scene->rec.normal);

}

void	handle_camera(int keycode, t_data *data)
{
	t_camera	*cam;
	t_mlx		*engine;	

	cam = &data->scene->camera;
	engine = data->engine;
	if (keycode == KEY_A)
		engine->trans = vplus_(engine->trans, -cam->u.x, 0, -cam->u.z);
	else if (keycode == KEY_D)
		engine->trans = vplus_(engine->trans, cam->u.x, 0, cam->u.z);
	else if (keycode == KEY_W)
		engine->trans = vplus_(engine->trans, -cam->w.x, 0, -cam->w.z);
	else if (keycode == KEY_S)
		engine->trans = vplus_(engine->trans, cam->w.x, 0, cam->w.z);
	else if (keycode == KEY_Q)
		engine->trans = vplus_(engine->trans, 0, 1, 0);
	else if (keycode == KEY_E)
		engine->trans = vplus_(engine->trans, 0, -1, 0);
	else
		handle_camera_i_hate_norm(keycode, data);
}

static void	handle_camera_i_hate_norm(int keycode, t_data *data)
{
	t_camera	*cam;
	t_mlx		*engine;	

	cam = &data->scene->camera;
	engine = data->engine;
	if (keycode == KEY_C && engine->fov > 5)
		engine->fov -= 5;
	else if (keycode == KEY_Z && engine->fov < 175)
		engine->fov += 5;
	else if (keycode == KEY_LEFT && engine->rotate.z < 90)
		engine->rotate.z += 5;
	else if (keycode == KEY_RIGHT && engine->rotate.z > -90)
		engine->rotate.z -= 5;
	else if (keycode == KEY_L)
		data->scene->selected_obj = data->scene->light;
	else if (keycode == KEY_ESC)
		terminate((void *)data);
}
