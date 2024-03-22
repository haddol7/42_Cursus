/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:54:28 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 20:45:58 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	leak(void)
{
	system("leaks fdf");
}

static void	init(t_client *data);

int	main(int argc, char **argv)
{
	t_client	data;

	atexit(leak);
	if (argc != 2)
		fdf_error(ERR_ARGC);
	init(&data);
	init_map(&data.map);
	load_map(argv[1], &data);
	mlx_hook(data.win, 2, 0, key_hook, &data);
	mlx_hook(data.win, 4, 0, mouse_press_hook, &data);
	mlx_hook(data.win, 5, 0, mouse_release_hook, &data);
	mlx_hook(data.win, 6, 0, mouse_drag_hook, &data);
	mlx_hook(data.win, 17, 0, terminate, &data);
	mlx_loop(data.mlx);
	return (0);
}

static void	init(t_client *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		fdf_error(ERR_MLX);
	data->win = mlx_new_window(data->mlx, WINDOW_X_SIZE, WINDOW_Y_SIZE, \
				"FDF - daeha");
	if (data->win == NULL)
		fdf_error(ERR_MLX);
	data->img.id = mlx_new_image(data->mlx, WINDOW_X_SIZE, WINDOW_Y_SIZE);
	if (data->img.id == NULL)
		fdf_error(ERR_MLX);
	data->img.addr = mlx_get_data_addr(data->img.id, &data->img.bits_per_pixel, \
					&data->img.line_size, &data->img.endian);
}
