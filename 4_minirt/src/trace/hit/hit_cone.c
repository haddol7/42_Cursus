/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:55:57 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/25 14:58:44 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

// void	debug(char *str, t_vec3 vec)
// {
// 	dprintf(2, "%s -> %f %f %f\n", str, vec.x, vec.y, vec.z);
// }

t_discriminant	cal_discriminant(t_cone *co, t_ray *ray)
{
	t_discriminant	dis;
	t_point3		oc;

	ft_memset(&dis, 0, sizeof(t_discriminant));
	oc = vminus(ray->orig, co->center);
	dis.a = vdot(ray->dir, ray->dir) - (vdot(ray->dir, co->normalize) \
				* vdot(ray->dir, co->normalize));
	dis.half_b = vdot(ray->dir, oc) - vdot(ray->dir, co->normalize) * \
				vdot(oc, co->normalize);
	dis.c = vdot(oc, oc) - (vdot(oc, co->normalize) * \
				vdot(oc, co->normalize)) - co->radius2;
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
	if (dot_len >= 0 && dot_len <= cy->height)
	{
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

t_bool	hit_cone_side(t_object *co_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone			*co;
	t_discriminant	dis;
	double			root[2];

	co = co_obj->element;
	dis = cal_discriminant(co, ray);
	if (dis.discriminant < 0)
		return (FALSE);
	root[0] = ((-dis.half_b) - dis.sqrtd) / dis.a;
	root[1] = ((-dis.half_b) + dis.sqrtd) / dis.a;
	if ((root[0] < rec->tmin || root[0] > rec->tmax) && \
			(root[1] < rec->tmin || root[1] > rec->tmax))
		return (FALSE);
	if (is_root_valid(rec, ray, co_obj, root[0]) == TRUE)
	{
		rec->tmax = root[0];
		return (TRUE);
	}
	else if (is_root_valid(rec, ray, co_obj, root[1]) == TRUE)
	{
		rec->tmax = root[1];
		return (TRUE);
	}
	return (FALSE);
}

t_bool	hit_cone_cap(t_object *co_obj, t_ray *ray, \
			t_hit_record *rec, t_point3 center)
{
	t_cone			*co;
	t_hit_record	rec_tmp;
	double			root;
	double			r;

	co = co_obj->element;
	if (vdot(co->normalize, ray->dir) == 0)
		return (FALSE);
	root = vdot(vminus(center, ray->orig), co->normalize) \
				/ vdot(co->normalize, ray->dir);
	rec_tmp = *rec;
	rec_tmp.t = root;
	rec_tmp.p = ray_at(ray, root);
	r = vlength2(vminus(rec_tmp.p, center));
	if (!(root < rec->tmin || root > rec->tmax || root < 0) \
			&& (0 <= r && r <= co->radius2))
	{
		*rec = rec_tmp;
		rec->normal = co->normalize;
		set_face_normal(ray, rec);
		rec->albedo = co_obj->albedo;
		rec->tmax = root;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	hit_cone(t_object *co_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone	*co;
	int		hit;

	co = co_obj->element;
	hit = 0;
	if (hit_cylinder_side(co_obj, ray, rec))
		hit++;
	if (hit_cylinder_cap(co_obj, ray, rec, co->center))
		hit++;
	if (hit != 0)
		return (TRUE);
	return (FALSE);
}
