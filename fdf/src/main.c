/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:54:28 by daeha             #+#    #+#             */
/*   Updated: 2024/03/16 14:41:31 by daeha            ###   ########.fr       */
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

#include <stdio.h>

int main(int argc, char **argv)
{
	t_client	data;

	if (argc != 2)
		fdf_error(ERR_ARGC);
	init(&data);
	load_map(argv[1], &data.map);

	mlx_loop(data.mlx);
	return (0);
}
