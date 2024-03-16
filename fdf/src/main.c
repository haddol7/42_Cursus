/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:54:28 by daeha             #+#    #+#             */
/*   Updated: 2024/03/16 15:28:55 by daeha            ###   ########.fr       */
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

void draw(t_map map, t_img *img, void *mlx, void *win)
{
	size_t	col;
	size_t	row;

	row = 0;
	while (row < map.row)
	{
		col = 0;
		while (col + 1 < map.col)
		{
			put_line_to_image(img->addr, map.point[col * (row + 1)], map.point[(col + 1) * (row + 1)]);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(mlx, win, img->id, 0, 0);
}

int main(int argc, char **argv)
{
	t_client	data;

	if (argc != 2)
		fdf_error(ERR_ARGC);
	init(&data);
	load_map(argv[1], &data.map);
//	mlx_hook(data.win, 2, 0, key_press_for_test, &data);
	draw(data.map, &data.img, data.mlx, data.win);
	mlx_loop(data.mlx);
	return (0);
}
