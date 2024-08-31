/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:27 by daeha             #+#    #+#             */
/*   Updated: 2024/08/31 23:08:25 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libft.h"
#include "utils.h"

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere	*sp;

	sp = (t_sphere *)ft_malloc(sizeof(t_sphere));
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_cylinder	*cylinder(t_point3 center, t_vec3 normal, \
						double diameter, double height)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)ft_malloc(sizeof(t_cylinder));
	cy->center = center;
	cy->height = height;
	cy->normal = normal;
	cy->radius = diameter / 2;
	cy->radius2 = cy->radius * cy->radius;
	return (cy);
}

t_plane	*plane(t_point3 center, t_vec3 normal)
{
	t_plane	*pl;

	pl = (t_plane *)ft_malloc(sizeof(t_plane));
	pl->center = center;
	pl->normal = normal;
	return (pl);
}

t_light	*light_point(t_point3 light_origin, \
					t_color3 light_color, double bright_ratio)
{
	t_light	*light;

	light = (t_light *)ft_malloc(sizeof(t_light));
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

t_cone	*cone(t_point3 center, t_vec3 normalize, \
				double diameter, double height)
{
	t_cone	*cone;

	cone = (t_cone *)ft_malloc(sizeof(t_cone));
	cone->center = center;
	cone->height = height;
	cone->radius = diameter / 2;
	cone->radius2 = cone->radius * cone->radius;
	cone->normalize = vmult(normalize, -1);
	return (cone);
}
