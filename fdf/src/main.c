/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:54:28 by daeha             #+#    #+#             */
/*   Updated: 2024/03/20 22:30:12 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init(t_client *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		fdf_error(ERR_MLX);
	data->win = mlx_new_window(data->mlx, WINDOW_X_SIZE, WINDOW_Y_SIZE, "FDF");
	if (data->win == NULL)
		fdf_error(ERR_MLX);
	data->img.id = mlx_new_image(data->mlx, WINDOW_X_SIZE, WINDOW_Y_SIZE);
	if (data->img.id == NULL)
		fdf_error(ERR_MLX);
	data->img.addr = mlx_get_data_addr(data->img.id, &data->img.bits_per_pixel, &data->img.line_size, &data->img.endian);
}

int key_hook(int keycode, t_client *data)
{
	if (keycode == KEY_A)
		data->map.angular.z += 1;
	else if (keycode == KEY_D)
		data->map.angular.z -= 1;
	else if (keycode == KEY_W)
		data->map.angular.x += 1;
	else if (keycode == KEY_S)
		data->map.angular.x -= 1;
	else if (keycode == KEY_Q)
		data->map.angular.y += 1;
	else if (keycode == KEY_E)
		data->map.angular.y -= 1;
	else if (keycode == KEY_C)
	{
		data->map.angular.x = 0;
		data->map.angular.y = 0;
		data->map.angular.z = 0;
	}
	draw(data->map, &data->img, data->mlx, data->win);
	return (0);
}

int mouse_press_hook(int keycode, int x, int y, t_client *data)
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
		data->map.scale += 1;
	else if (keycode == MOUSE_DOWN && data->map.scale > 0)
		data->map.scale -= 1;
	draw(data->map, &data->img, data->mlx, data->win);
	return (0);
}

int mouse_release_hook(int keycode, int x, int y, t_client *data)
{
	data->mouse.is_pressed = 0;
	data->mouse.x = x;
	data->mouse.y = y;
	return (0);
}

int mouse_drag_hook(int x, int y, t_client *data)
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

void	init_map(t_map *map)
{
	map->translate.x = 0;
	map->translate.y = 0;
	map->translate.z = 0;
	map->angular.x = 0;
	map->angular.y = 0;
	map->angular.z = 0;
}

int main(int argc, char **argv)
{
	t_client	data;

	if (argc != 2)
		fdf_error(ERR_ARGC);
	init(&data);
	init_map(&data.map);
	load_map(argv[1], &data);
	mlx_hook(data.win, 2, 0, key_hook, &data);
	mlx_hook(data.win, 4, 0, mouse_press_hook, &data);
	mlx_hook(data.win, 5, 0, mouse_release_hook, &data);
	mlx_hook(data.win, 6, 0, mouse_drag_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
