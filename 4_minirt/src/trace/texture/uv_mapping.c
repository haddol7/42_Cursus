/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:31:49 by daeha             #+#    #+#             */
/*   Updated: 2024/09/07 15:48:01 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

static void	uv_mapping_sp(double uv[2], t_hit_record *rec, \
							t_texture *t, t_sphere *sp);
static void	uv_mapping_pl(double uv[2], t_hit_record *rec, \
							t_texture *t, t_plane *pl);
static void	uv_mapping_cy(double uv[2], t_hit_record *rec, \
							t_texture *t, t_cylinder *cy);
static void	uv_mapping_co(double uv[2], t_hit_record *rec, \
							t_texture *t, t_cone *co);

void	uv_mapping(double uv[2], t_object *obj, \
					t_texture *tex, t_hit_record *rec)
{
	if (obj->type == SP)
		uv_mapping_sp(uv, rec, tex, (t_sphere *)obj->element);
	else if (obj->type == PL)
		uv_mapping_pl(uv, rec, tex, (t_plane *)obj->element);
	else if (obj->type == CY)
		uv_mapping_cy(uv, rec, tex, (t_cylinder *)obj->element);
	else if (obj->type == CO)
		uv_mapping_co(uv, rec, tex, (t_cone *)obj->element);
}

static void	uv_mapping_sp(double uv[2], t_hit_record *rec, \
							t_texture *t, t_sphere *sp)
{
	t_point3	o;
	double		theta;
	double		phi;

	o.x = rec->p.x - sp->center.x;
	o.y = rec->p.y - sp->center.y;
	o.z = rec->p.z - sp->center.z;
	theta = acos(-o.y / sp->radius);
	phi = atan2(-o.z, o.x) + M_PI;
	uv[U] = (phi / (2 * M_PI));
	uv[V] = (1 - (theta / (M_PI)));
	if (t)
	{
		uv[U] *= t->width;
		uv[V] *= t->height;
	}
}

static void	uv_mapping_pl(double uv[2], t_hit_record *rec, \
						t_texture *t, t_plane *pl)
{
	t_point3	o;

	o = uv_axis_mapping(pl->center, pl->normal, rec);
	if (t)
	{
		uv[U] = (int)fabs(o.x) % t->width;
		uv[V] = (int)fabs(o.z) % t->height;
	}
	else
	{
		uv[U] = fabs(o.x / 100);
		uv[V] = fabs(o.z / 100);
	}
}

static void	uv_mapping_cy(double uv[2], t_hit_record *rec, \
							t_texture *t, t_cylinder *cy)
{
	t_point3	o;
	double		phi;

	o = uv_axis_mapping(cy->center, cy->normal, rec);
	phi = atan2(-o.z, o.x) + M_PI;
	uv[U] = (phi / (2 * M_PI));
	uv[V] = fabs((cy->height - o.y) / cy->height);
	if (t)
	{
		uv[U] *= t->width;
		uv[V] *= t->height;
	}
}

static void	uv_mapping_co(double uv[2], t_hit_record *rec, \
							t_texture *t, t_cone *co)
{
	t_point3	o;
	double		phi;

	o = uv_axis_mapping(co->center, co->normalize, rec);
	phi = atan2(-o.z, o.x) + M_PI;
	uv[U] = (phi / (2 * M_PI));
	uv[V] = fabs(o.y / co->height);
	if (t)
	{
		uv[U] *= t->width;
		uv[V] *= t->height;
		if (uv[V] >= t->height)
			uv[V] = t->height - 1;
	}
}
