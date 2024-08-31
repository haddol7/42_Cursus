/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:55:57 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/31 15:59:55 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

t_discriminant	cal_discriminant_cone(t_cone *co, t_ray *ray)
{
	t_discriminant	dis;
	double			cos2;

	ft_memset(&dis, 0, sizeof(t_discriminant));
	cos2 = pow(co->height, 2) / (pow(co->height, 2) + co->radius2);
	dis.a = pow(vdot(ray->dir, co->normalize), 2) - cos2;
	dis.half_b = vdot(ray->dir, co->normalize) * vdot(vminus(ray->orig, co->center), co->normalize) - vdot(vminus(ray->orig, co->center), ray->dir) * cos2;
	dis.c =  pow(vdot(vminus(ray->orig, co->center), co->normalize), 2) - vlength2(vminus(ray->orig, co->center)) * cos2;
	dis.discriminant = (dis.half_b * dis.half_b) - (dis.a * dis.c);
	if (dis.discriminant >= 0)
		dis.sqrtd = sqrt(dis.discriminant);
	return (dis);
}
//TODO ::  탄젠트 값을 사용하여 반지름을 제어하면?!?!?!?!
t_bool	is_root_valid_cone(t_hit_record *rec, t_ray *ray, \
		t_object *co_obj, double root)
{
	// double			dot_len;
	t_cone			*co;
	t_hit_record	rec_tmp;

	co = co_obj->element;
	rec_tmp = *rec;
	rec_tmp.t = root;
	rec_tmp.p = ray_at(ray, root);
	// dot_len = vdot(vminus(rec_tmp.p, co->center), co->normalize);

		*rec = rec_tmp;
		// rec->normal =  /
		set_face_normal(ray, rec);
		rec->albedo = co_obj->albedo;
	return (TRUE);
}

t_bool	hit_cone_side(t_object *co_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone			*co;
	t_discriminant	dis;
	double			root[2];

	co = co_obj->element;
	dis = cal_discriminant_cone(co, ray);
	if (dis.discriminant < 0)
		return (FALSE);
	root[0] = ((-dis.half_b) - dis.sqrtd) / dis.a;
	root[1] = ((-dis.half_b) + dis.sqrtd) / dis.a;
	if (is_root_valid_cone(rec, ray, co_obj, root[0]) == TRUE)
	{
		if (root[0] < rec->tmin || root[0] > rec->tmax)
			return (FALSE);
		rec->tmax = root[0];
		return (TRUE);
	}
	else if (is_root_valid_cone(rec, ray, co_obj, root[1]) == TRUE)
	{
		if (root[1] < rec->tmin || root[1] > rec->tmax)
			return (FALSE);
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
	if (hit_cone_side(co_obj, ray, rec))
		hit++;
	if (hit_cone_cap(co_obj, ray, rec, co->center))
		hit++;
	if (hit != 0)
		return (TRUE);
	return (FALSE);
}
