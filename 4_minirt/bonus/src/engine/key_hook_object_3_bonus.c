/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_object_3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:51:11 by jungslee          #+#    #+#             */
/*   Updated: 2024/09/07 18:51:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
