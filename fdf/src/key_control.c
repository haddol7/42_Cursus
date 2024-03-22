/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:49:53 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 15:50:02 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_client *data)
{
	if (keycode == KEY_A)
		data->map.angular.z += 5;
	else if (keycode == KEY_D)
		data->map.angular.z -= 5;
	else if (keycode == KEY_W)
		data->map.angular.x += 5;
	else if (keycode == KEY_S)
		data->map.angular.x -= 5;
	else if (keycode == KEY_Q)
		data->map.angular.y += 5;
	else if (keycode == KEY_E)
		data->map.angular.y -= 5;
	else if (keycode == KEY_C)
	{
		data->map.angular.x = 0;
		data->map.angular.y = 0;
		data->map.angular.z = 0;
		data->map.translate.x = 0;
		data->map.translate.y = 0;
		data->map.translate.z = 0;
	}
	draw(data->map, &data->img, data->mlx, data->win);
	return (0);
}

int	mouse_press_hook(int keycode, int x, int y, t_client *data)
{
	if (keycode == MOUSE_LEFT)
	{
		data->mouse.is_pressed = 1;
		data->mouse.x = x;
		data->mouse.y = y;
	}
	else if (keycode == MOUSE_RIGHT)
	{
		data->mouse.is_pressed = 2;
		data->mouse.x = x;
		data->mouse.y = y;
	}
	else if (keycode == MOUSE_UP)
		data->map.scale += 0.5;
	else if (keycode == MOUSE_DOWN && data->map.scale > 0)
		data->map.scale -= 0.5;
	draw(data->map, &data->img, data->mlx, data->win);
	return (0);
}

int	mouse_release_hook(int keycode, int x, int y, t_client *data)
{
	if (keycode == MOUSE_LEFT || keycode == MOUSE_RIGHT)
	{
		data->mouse.is_pressed = 0;
		data->mouse.x = x;
		data->mouse.y = y;
	}
	return (0);
}

int	mouse_drag_hook(int x, int y, t_client *data)
{
	if (data->mouse.is_pressed == 1)
	{
		data->map.angular.x = x - data->mouse.x;
		data->map.angular.y = y - data->mouse.y;
	}
	else if (data->mouse.is_pressed == 2)
	{
		data->map.translate.x = x - data->mouse.x;
		data->map.translate.y = y - data->mouse.y;
	}
	draw(data->map, &data->img, data->mlx, data->win);
	return (0);
}
