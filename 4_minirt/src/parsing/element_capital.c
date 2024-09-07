/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_capital.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:53:14 by jungslee          #+#    #+#             */
/*   Updated: 2024/09/07 17:11:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_object	*is_valid_a(char **split, t_scene *scene)
{
	static int	count = 0;

	scene->ka = ft_atof(split[1]);
	scene->ambient = vmult(check_color(split[2]), scene->ka / 255);
	if (is_valid_ratio_range(scene->ka) == 0)
		error_exit("A : ka is invalid\n");
	if (split[3] != NULL || count != 0)
		error_exit("A : invalid\n");
	count++;
	return (0);
}

t_object	*is_valid_c(char **split, t_scene *scene, t_mlx *engine)
{
	static int	count = 0;
	t_vec3		rotated_vec;
	t_vec3		axis;
	double		theta;

	engine->trans = check_coordinate(split[1]);
	rotated_vec = vunit(check_normalize_vector(split[2]));
	axis = vcross(vec3(0, 0, -1), rotated_vec);
	if (vlength2(axis) != 0)
	{	
		rotated_vec = vunit(rotated_vec);
		theta = acos(vdot(vec3(0, 0, 1), rotated_vec));
		engine->rotate.x = theta * rotated_vec.y * 180 / M_PI;
		engine->rotate.y = theta * rotated_vec.x * 180 / M_PI;
	}
	else
		ft_memset(&engine->rotate, 0, sizeof(t_vec3));
	engine->fov = ft_atof(split[3]);
	if (split[4] != NULL || count != 0)
		error_exit("C : invalid\n");
	scene->camera = camera(scene, *engine);
	count++;
	return (0);
}

t_object	*is_valid_l(char **split, t_scene *scene)
{
	static int	count = 0;
	t_point3	point;
	t_color3	color;
	double		ratio;
	t_object	*light;

	point = check_coordinate(split[1]);
	ratio = ft_atof(split[2]);
	color = check_color(split[3]);
	if (is_valid_ratio_range(ratio) == 0)
		error_exit("L : invalid light ratio\n");
	if (split[4] != NULL || count != 0)
		error_exit("L : invalid\n");
	light = object_default(LIGHT_POINT, \
		light_point(point, color, ratio), color);
	scene->light = light;
	return (0);
}
