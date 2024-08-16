/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:00 by daeha             #+#    #+#             */
/*   Updated: 2024/08/16 19:23:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include "libft.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3 ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray ray;

	ray.orig = cam->orig;
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_hit_record record_init(void)
{
	t_hit_record record;

	ft_memset(&record, 0, sizeof(t_hit_record));
	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

static t_bool temp_hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec, t_object *select, t_bool *is_outline)
{
    t_vec3  oc;
	t_sphere *sp;
    double  a;
    double  half_b;
    double  c;
    double  discriminant;
	double	sqrtd;
	double	root;
	
	sp = sp_obj->element;
	oc = vminus(ray->orig, sp->center);
    a = vlength2(ray->dir);
    half_b = vdot(oc, ray->dir);
    c = vlength2(oc) - sp->radius2;
    discriminant = half_b * half_b - a * c;
	
	//dprintf(2, "c %f dis %f\n", c, discriminant);
    if (discriminant < -0.001 * vlength2(oc))
		return (FALSE);
	else if (discriminant > -0.001 * vlength2(oc) && discriminant < 0.001 * vlength2(oc) && sp_obj == select)
		*is_outline = TRUE;
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);

	if (sp_obj->is_checker)
		rec->albedo = texture_checkerboard(rec->p, sp);
	else if (sp_obj->texture.img.id)
		rec->albedo = texture(rec->p, sp, sp_obj->texture);
	else
		rec->albedo = sp_obj->albedo;
	return (TRUE);
}

static t_bool	temp_hit_obj(t_object *world, t_ray *ray, t_hit_record *rec, t_object *select, t_bool *is_outline)
{
	t_bool		hit_result;
	
	hit_result = FALSE;
	if (world->type == SP)
		hit_result = temp_hit_sphere(world, ray, rec, select, is_outline);
	return (hit_result);
}

static t_object	*temp_hit_outline(t_scene *scene, t_ray *ray, t_hit_record *rec, t_bool *is_outline)
{
	t_hit_record	temp_rec;
	t_object		*world;

	world = scene->world;
	temp_rec = *rec;
	temp_rec.object = NULL;
	while (world)
	{
		if (temp_hit_obj(world, ray, &temp_rec, scene->selected_obj, is_outline))
		{
			temp_rec.tmax = temp_rec.t;
			temp_rec.object = world;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (temp_rec.object);
}

t_color3    ray_color(t_scene *scene, t_color3 color)
{
    double		t;
	t_object	*hit_obj;
	t_bool		is_outline;
	
    scene->rec = record_init();
	is_outline = FALSE;
	//hit_obj = hit(scene->world, &scene->ray, &scene->rec);
	hit_obj = temp_hit_outline(scene, &scene->ray, &scene->rec, &is_outline);
	if (is_outline)
		return (vec3(1, 1, 0));
	else if (hit_obj)
		return (vplus(phong_lighting(scene), color));
    else
    {
        t = 0.5 * (scene->ray.dir.y + 1.0);
        return (vplus(vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)), color));
    }
}

t_vec3	sample_square(void)
{
	return (vec3(random_double() - 0.5, random_double() - 0.5, 0));
}

