/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:00 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 19:38:30 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include "libft.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3	ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, \
					vmult(cam->horizontal, u)), \
					vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_hit_record	record_init(void)
{
	t_hit_record	record;

	ft_memset(&record, 0, sizeof(t_hit_record));
	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

t_color3	ray_color(t_scene *scene, t_color3 color)
{
	t_bool		is_outline;

	scene->rec = record_init();
	is_outline = FALSE;
	if (hit(scene->world, &scene->ray, &scene->rec))
		return (vplus(phong_lighting(scene), color));
	else
		return (vec3(0, 0, 0));
}
