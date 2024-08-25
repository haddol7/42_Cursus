/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:42:40 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/25 17:51:02 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

t_discriminant	cal_discriminant(t_cylinder *cy, t_ray *ray)
{
	t_discriminant	dis;
	t_point3		oc;

	ft_memset(&dis, 0, sizeof(t_discriminant));
	oc = vminus(ray->orig, cy->center);
	dis.a = vdot(ray->dir, ray->dir) - (vdot(ray->dir, cy->normal) \
			* vdot(ray->dir, cy->normal));
	dis.half_b = vdot(ray->dir, oc) - vdot(ray->dir, cy->normal) \
			* vdot(oc, cy->normal);
	dis.c = vdot(oc, oc) - (vdot(oc, cy->normal) * \
				vdot(oc, cy->normal)) - cy->radius2;
	dis.discriminant = (dis.half_b * dis.half_b) - (dis.a * dis.c);
	if (dis.discriminant >= 0)
		dis.sqrtd = sqrt(dis.discriminant);
	return (dis);
}

t_bool	is_root_valid(t_hit_record *rec, t_ray *ray, \
						t_object *cy_obj, double root)
{
	double			dot_len;
	t_cylinder		*cy;
	t_hit_record	rec_tmp;

	cy = cy_obj->element;
	rec_tmp = *rec;
	rec_tmp.t = root;
	rec_tmp.p = ray_at(ray, root);
	dot_len = vdot(vminus(rec_tmp.p, cy->center), cy->normal);
	if (dot_len > 0 && dot_len < cy->height)
	{
		if (root <= rec->tmin || root >= rec->tmax)
			return (FALSE);
		*rec = rec_tmp;
		rec->normal = vunit(vminus(vminus(rec->p, cy->center), \
						vmult(cy->normal, dot_len)));
		set_face_normal(ray, rec);
		rec->albedo = cy_obj->albedo;
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool	hit_cylinder_cap(t_object *cy_obj, t_ray *ray, \
					t_hit_record *rec, t_point3 center)
{
	t_cylinder		*cy;
	t_hit_record	rec_tmp;
	double			root;
	double			r;

	cy = cy_obj->element;
	if (vdot(cy->normal, ray->dir) == 0)
		return (FALSE);
	root = vdot(vminus(center, ray->orig), cy->normal) \
					/ vdot(cy->normal, ray->dir);
	rec_tmp = *rec;
	rec_tmp.t = root;
	rec_tmp.p = ray_at(ray, root);
	r = vlength2(vminus(rec_tmp.p, center));
	if (!(root < rec->tmin || root > rec->tmax || root < 0) \
				&& (0 <= r && r <= cy->radius2))
	{
		*rec = rec_tmp;
		rec->normal = cy->normal;
		set_face_normal(ray, rec);
		rec->albedo = cy_obj->albedo;
		rec->tmax = root;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder		*cy;
	t_discriminant	dis;
	double			root[2];

	cy = cy_obj->element;
	dis = cal_discriminant(cy, ray);
	if (dis.discriminant < 0)
		return (FALSE);
	root[0] = ((-dis.half_b) - dis.sqrtd) / dis.a;
	root[1] = ((-dis.half_b) + dis.sqrtd) / dis.a;
	if (is_root_valid(rec, ray, cy_obj, root[0]) == TRUE)
	{
		rec->tmax = root[0];
		return (TRUE);
	}
	else if (is_root_valid(rec, ray, cy_obj, root[1]) == TRUE)
	{
		rec->tmax = root[1];
		return (TRUE);
	}
	return (FALSE);
}

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	int			hit;

	cy = cy_obj->element;
	hit = 0;
	if (hit_cylinder_cap(cy_obj, ray, rec, cy->center))
		hit++;
	if (hit_cylinder_cap(cy_obj, ray, rec, \
			vplus(cy->center, vmult(cy->normal, cy->height))))
		hit++;
	if (hit_cylinder_side(cy_obj, ray, rec))
	{
		if (cy_obj->bump.img.id)
			rec->normal = bump(cy_obj, &cy_obj->bump, rec);
		if (cy_obj->texture.img.id)
			rec->albedo = texture(cy_obj, &cy_obj->texture, rec);
		else if (cy_obj->is_checker == TRUE)
			rec->albedo = checkerboard(cy_obj, rec);
		else
			rec->albedo = cy_obj->albedo;
		hit++;
	}
	if (hit == 0)
		return (FALSE);
	return (TRUE);
}
