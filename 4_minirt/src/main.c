/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:19 by daeha             #+#    #+#             */
/*   Updated: 2024/08/20 21:50:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TODO: capital_ob
//TODO: rand() 수정
t_scene	*scene_init(int fd, t_mlx *engine)
{
	t_scene	*scene;
	int		capital_ob;

	capital_ob = 0;
	scene = (t_scene *)ft_malloc(sizeof(t_scene));
	scene->canvas = canvas(WINDOW_W, WINDOW_H);
	map_validity(fd, scene, &capital_ob, engine);
	if (capital_ob != 3)
		error_exit("too many capital object");
	return (scene);
}

t_mlx	*engine_init(void)
{
	t_mlx	*engine;

	engine = (t_mlx *)ft_malloc(sizeof(t_mlx));
	engine->mlx = mlx_init();
	if (engine->mlx == NULL)
		exit(ERR_MLX);
	engine->win = mlx_new_window(engine->mlx, WINDOW_W, WINDOW_H, "minirt");
	if (engine->win == NULL)
		exit(ERR_MLX);
	engine->img = (t_img *)ft_malloc(sizeof(t_img));
	engine->img->id = mlx_new_image(engine->mlx, WINDOW_W, WINDOW_H);
	if (engine->img->id == NULL)
		exit(ERR_MLX);
	engine->img->addr = mlx_get_data_addr(engine->img->id, \
						&engine->img->bits_per_pixel, \
						&engine->img->line_size, &engine->img->endian);
	engine->fov = 60;
	return (engine);
}

int	main(int argc, char *argv[])
{	
	int			fd;
	t_data		data;

	fd = argument_validity(argc, argv[1]);
	data.engine = engine_init();
	data.scene = scene_init(fd, data.engine);
	draw_ray_orig(data.scene, data.engine);
	mlx_hook(data.engine->win, 2, 0, key_hook, &data);
	mlx_hook(data.engine->win, 4, 0, mouse_press_hook, &data);
	mlx_hook(data.engine->win, 5, 0, mouse_release_hook, &data);
	mlx_hook(data.engine->win, 6, 0, mouse_drag_hook, &data);
	mlx_hook(data.engine->win, 17, 0, terminate, &data);
	mlx_loop(data.engine->mlx);
	return (0);
}
