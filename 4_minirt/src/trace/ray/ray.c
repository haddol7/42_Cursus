/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:00 by daeha             #+#    #+#             */
/*   Updated: 2024/08/24 21:40:28 by jungslee         ###   ########.fr       */
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


// void	debug(char *str, t_vec3 vec)
// {
// 	dprintf(2, "%s -> %f %f %f\n", str, vec.x, vec.y, vec.z);
// }

// void	print_rec(t_hit_record rec)
// {
// 	debug("p : ", rec.p);
// 	debug("normal : ", rec.normal);
// 	printf("tmin : %f\n", rec.tmin);
// 	printf("tmax : %f\n", rec.tmax);
// 	printf("t : %f\n", rec.t);
// 	debug("albedo :\n", rec.albedo);
// }

t_color3	ray_color(t_scene *scene, t_color3 color)
{
	scene->rec = record_init();
	t_light	*light;

	light = scene->light->element;
	if (hit(scene->world, &scene->ray, &scene->rec))
	{
		// print_rec(scene->rec);
		// debug("light dir -> ", vminus(light->origin, scene->rec.p));
		return (vplus(phong_lighting(scene), color));
	}
	else
		return (vec3(0.2, 0.2, 0.2));
}
