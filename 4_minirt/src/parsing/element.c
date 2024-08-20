/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:37 by daeha             #+#    #+#             */
/*   Updated: 2024/08/20 15:22:46 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
}

int	count_split_words(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

t_point3	check_coordinate(char *coor)
{
	double	x;
	double	y;
	double	z;
	char	**split;

	split = ft_split(coor, ',');
	if (count_split_words(split) != 3)
		error_exit("not a complete coordinate\n");
	x = ft_atof(split[0]);
	y = ft_atof(split[1]);
	z = ft_atof(split[2]);
	// if (split[3] != NULL)
	// 	error_exit("check_coordinate\n");
	free_split(split);
	return (point3(x, y, z));
}

int	is_in_valid_normalize_range(double x, double y, double z)
{
	if (!(-1.0 <= x && x <= 1.0))
		return (0);
	if (!(-1.0 <= y && y <= 1.0))
		return (0);
	if (!(-1.0 <= z && z <= 1.0))
		return (0);
	return (1);
}

t_vec3	check_normalize_vector(char *coor)
{
	double	x;
	double	y;
	double	z;
	char	**split;

	split = ft_split(coor, ',');
	if (count_split_words(split) != 3)
		error_exit("not a complete vector\n");
	x = ft_atof(split[0]);
	y = ft_atof(split[1]);
	z = ft_atof(split[2]);
	if (is_in_valid_normalize_range(x, y, z) == 0)
		error_exit("not_valid_normalize_vector\n");
	// if (split[3] != NULL)
	// 	error_exit("check_normalize vector\n");
	free_split(split);
	return (vec3(x, y, z));
}

int	is_color_in_valid_range(double r, double g, double b)
{
	if (!(0.0 <= r && r <= 1.0))
		return (0);
	if (!(0.0 <= g && g <= 1.0))
		return (0);
	if (!(0.0 <= b && b <= 1.0))
		return (0);
	return (1);
}

int	is_valid_ratio_range(double ratio)
{
	if (!(0.0 <= ratio && ratio <= 1.0))
		return (0);
	return (1);
}

t_color3	check_color(char *color)
{
	double	r;
	double	g;
	double	b;
	char	**split;

	split = ft_split(color, ',');
	if (count_split_words(split) != 3)
		error_exit("not complete rgb\n");
	r = ft_atof(split[0]) / 255;
	g = ft_atof(split[1]) / 255;
	b = ft_atof(split[2]) / 255;
	if (is_color_in_valid_range(r, g, b) == 0)
		error_exit("not valid RGB range\n");
	// if (split[3] != NULL)
	// 	error_exit("check_color\n");
	free_split(split);
	return (color3(r, g, b));
}

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
		sp = object_texture(SP, sphere(center, ft_atof(split[2])), texture, engine.mlx);
		free(texture);
	}
	else if (split[4] == NULL || (split[4][0] == '\n' && split[5] == NULL))
		sp = object_default(SP, sphere(center, ft_atof(split[2])), color);
	else
		error_exit("check_is_valid_sp\n");
		//TODO 이미지 파일 검증 추가
	return (sp);
}

t_object	*is_valid_cy(char **split, t_mlx engine)
{
	t_object	*cy;
	char 		*texture;
	t_point3	center;
	t_vec3		normalize;
	t_color3	color;

	cy = NULL;
	center = check_coordinate(split[1]);
	normalize = check_normalize_vector(split[2]);
	color = check_color(split[5]);
	if (split[6] != NULL && split[6][0] != '\n')
	{
		texture = ft_strtrim(split[6], "\n");
		cy = object_texture(CY, cylinder(center, normalize, \
				ft_atof(split[3]), ft_atof(split[4])), texture, engine.mlx);
		free(texture);
	}
	else if (split[6] == NULL || (split[6][0] == '\n' && split[7] == NULL))
		cy = object_default(CY, cylinder(center, normalize, ft_atof(split[3]), ft_atof(split[4])), color);
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
	normalize = check_normalize_vector(split[2]);
	color = check_color(split[3]);
	if (split[4] != NULL &&  split[4][0] != '\n')
	{
		texture = ft_strtrim(split[4], "\n");
		pl = object_texture(PL, plane(center, normalize), texture, engine.mlx);
		free(texture);
	}
	else if (split[4] == NULL || (split[4][0] == '\n' && split[5] == NULL))
		pl = object_default(PL, plane(center, normalize), color);
	else
		error_exit("is_valid_pl\n");
				//TODO 이미지 파일 검증 추가
	return (pl);
}

t_object	*is_valid_A(char **split, t_scene *scene)
{
	static int	count = 0;
	
	scene->ka = ft_atof(split[1]);
	scene->ambient = vmult(check_color(split[2]), scene->ka / 255);
	if (is_valid_ratio_range(scene->ka) == 0)
		error_exit("not_valid_ratio : ka");
	if (split[3] != NULL || count != 0)
		error_exit("is_valid_A\n");
	count++;
	return (0);
}

t_object	*is_valid_C(char **split, t_scene *scene, t_mlx *engine)
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
		error_exit("is_valild_c\n");
	scene->camera = camera(scene, *engine);
	count++;
	return (0);
}

t_object	*is_valid_L(char **split, t_scene *scene)
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
		error_exit("not_valid_ratio_range : light ratio");
	if (split[4] != NULL || count != 0)
		error_exit("is_valid_L\n");//TODO 흠.. 라이트는 하나??
	light = object_default(LIGHT_POINT, light_point(point, color, ratio), color);
	scene->light = light;
	return (0);
}
