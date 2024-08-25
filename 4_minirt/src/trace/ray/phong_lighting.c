/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:54 by daeha             #+#    #+#             */
/*   Updated: 2024/08/25 14:42:01 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

static t_vec3	reflect(t_vec3 v, t_vec3 n);
static t_bool	in_shadow(t_scene *scene, t_vec3 d);

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	ret;
	t_object	*lights;

	ret = color3(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			ret = vplus(ret, point_light_get(scene, lights->element));
		lights = lights->next;
	}
	ret = vplus(ret, scene->ambient);
	return (vmin(vmult_(ret, scene->rec.albedo), color3(1, 1, 1)));
}

t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_vec3		light_dir;
	double		kd;
	t_color3	diffuse;
	t_color3	specular;
	t_vec3		view_dir;

	light_dir = vminus(light->origin, scene->rec.p);
	if (in_shadow(scene, light_dir))
		return (color3(0, 0, 0));
	light_dir = vunit(light_dir);
	view_dir = vunit(vmult(scene->ray.dir, -1));
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	diffuse = vmult(light->light_color, kd);
	light_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
	specular = vmult(vmult(light->light_color, KS), \
					pow(fmax(vdot(view_dir, light_dir), 0.0), KSN));
	return (vmult(vplus(diffuse, specular), light->bright_ratio * LUMEN));
}

static t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

static t_bool	in_shadow(t_scene *scene, t_vec3 d)
{
	t_hit_record	rec;
	t_ray			light_ray;
	double			light_len;

	light_len = vlength(d);
	light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), d);
	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(scene->world, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}
