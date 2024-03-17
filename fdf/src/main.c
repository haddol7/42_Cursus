/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:54:28 by daeha             #+#    #+#             */
/*   Updated: 2024/03/17 15:10:05 by daeha            ###   ########.fr       */
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

void	clean_img(t_img *img)
{
	int *img_addr;

	img_addr = (int *)img->addr;
	for (int i = 0; i < WINDOW_X_SIZE * WINDOW_Y_SIZE; i++)
		img_addr[i] = 0;
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
	clean_img(&data->img);
	draw(data->map, &data->img, data->mlx, data->win);
	return (0);
}

// int mouse_hook(int keycode, int x, int y, t_client *data)
// {
// 	if (keycode == MOUSE_LEFT)
// 	{
// 		data->map.translate.x += x;
// 		data->map.translate.y += y;
// 	}
// 	else if (keycode == MOUSE_RIGHT)
// 	else if (keycode == MOUSE_)
// }

int main(int argc, char **argv)
{
	t_client	data;

	if (argc != 2)
		fdf_error(ERR_ARGC);
	init(&data);
	load_map(argv[1], &data.map);


	scale(data.map.point, 3, data.map.row * data.map.col);
	data.map.angular.x = 0;
	data.map.angular.y = 0;
	data.map.angular.z = 0;

	mlx_hook(data.win, 2, 0, key_hook, &data);
//	mlx_hook(data.win, 4, 0, mouse_hook, &data);
	

//	mlx_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
