/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:54:40 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/25 14:55:29 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	t_vec3	oc;
	double	root;

	pl = pl_obj->element;
	oc = pl->center;
	root = (vdot(oc, pl->normal) - vdot(ray->orig, pl->normal)) \
				/ vdot(ray->dir, pl->normal);
	if (root < 0)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->normal;
	set_face_normal(ray, rec);
	if (pl_obj->bump.img.id)
		rec->normal = bump(pl_obj, &pl_obj->bump, rec);
	if (pl_obj->texture.img.id)
		rec->albedo = texture(pl_obj, &pl_obj->texture, rec);
	else if (pl_obj->is_checker == TRUE)
		rec->albedo = checkerboard(pl_obj, rec);
	else
		rec->albedo = pl_obj->albedo;
	if (rec->t < rec->tmin || rec->t > rec->tmax)
		return (FALSE);
	return (TRUE);
}
