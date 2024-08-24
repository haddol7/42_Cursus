/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:37 by daeha             #+#    #+#             */
/*   Updated: 2024/08/25 00:02:49 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_object	*is_valid_sp(char **split, t_mlx engine)
{
	t_object	*sp;
	char		*texture;
	t_point3	center;
	t_color3	color;

	sp = NULL;
	center = check_coordinate(split[1]);
	color = check_color(split[3]);
	if (split[4] != NULL && split[4][0] != '\n')
	{
		texture = ft_strtrim(split[4], "\n");
		sp = object_texture(SP, sphere(center, ft_atof(split[2])), \
			texture, engine.mlx);
		if (split[5] != NULL && *split[5] != '\n' && sp->texture.img.id != NULL)
			object_normal(sp, split[5], engine);
		free(texture);
	}
	else if (split[4] == NULL || (split[4][0] == '\n' && split[5] == NULL))
		sp = object_default(SP, sphere(center, ft_atof(split[2])), color);
	else
		error_exit("check_is_valid_sp\n");
	sp->albedo = color;
	return (sp);
}

t_object	*is_valid_cy(char **split, t_mlx engine)
{
	t_object	*cy;
	char		*texture;
	t_point3	center;
	t_vec3		normalize;
	t_color3	color;

	cy = NULL;
	center = check_coordinate(split[1]);
	normalize = vunit(check_normalize_vector(split[2]));
	color = check_color(split[5]);
	if (split[6] != NULL && split[6][0] != '\n')
	{
		texture = ft_strtrim(split[6], "\n");
		cy = object_texture(CY, cylinder(center, normalize, \
				ft_atof(split[3]), ft_atof(split[4])), texture, engine.mlx);
		free(texture);
	}
	else if (split[6] == NULL || (split[6][0] == '\n' && split[7] == NULL))
		cy = object_default(CY, cylinder(center, normalize, \
			ft_atof(split[3]), ft_atof(split[4])), color);
	else
		error_exit("check_is_valid_sp\n");
	return (cy);
}

t_object	*is_valid_pl(char **split, t_mlx engine)
{
	t_object	*pl;
	char		*texture;
	t_point3	center;
	t_vec3		normalize;
	t_color3	color;

	pl = NULL;
	center = check_coordinate(split[1]);
	normalize = vunit(check_normalize_vector(split[2]));
	color = check_color(split[3]);
	if (split[4] != NULL && split[4][0] != '\n')
	{
		texture = ft_strtrim(split[4], "\n");
		pl = object_texture(PL, plane(center, normalize), texture, engine.mlx);
		free(texture);
	}
	else if (split[4] == NULL || (split[4][0] == '\n' && split[5] == NULL))
		pl = object_default(PL, plane(center, normalize), color);
	else
		error_exit("is_valid_pl\n");
	return (pl);
}

t_object	*is_valid_co(char **split, t_mlx engine)
{
	t_object	*co;
	char		*texture;
	t_point3	center;
	t_point3	cross;
	t_vec3		normalize;

	co = NULL;
	center = check_coordinate(split[1]);
	cross = check_coordinate(split[2]);
	normalize = vunit(check_normalize_vector(split[3]));
	if (split[6] != NULL && split[6][0] != '\n')
	{
		texture = ft_strtrim(split[4], "\n");
		co = object_texture(CO, cone(center, normalize, \
				ft_atof(split[4]), cross), texture, engine.mlx);
		free(texture);
	}
	else if (split[6] == NULL || (split[6][0] == '\n' && split[7] == NULL))
		co = object_default(CO, cone(center, normalize, \
			ft_atof(split[4]), cross), check_color(split[5]));
	else
		error_exit("is_valid_co\n");
	return (co);
}
