/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:54:28 by daeha             #+#    #+#             */
/*   Updated: 2024/03/16 20:13:25 by daeha            ###   ########.fr       */
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

int rotate(int keycode, t_client *data)
{
	static float i = 0;

	size_t size;
	size = data->map.row * data->map.col;
	keycode = 1;

	data->map.translate.z += 10;
	clean_img(&data->img);
	draw(data->map, &data->img, data->mlx, data->win);
	
	return (0);
}

int main(int argc, char **argv)
{
	t_client	data;

	if (argc != 2)
		fdf_error(ERR_ARGC);
	init(&data);
	load_map(argv[1], &data.map);
	scale(data.map.point, 50, data.map.row * data.map.col);

	mlx_hook(data.win, 2, 0, rotate, &data);
	mlx_loop(data.mlx);
	return (0);
}
