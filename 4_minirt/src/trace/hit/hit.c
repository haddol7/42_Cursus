/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:35 by daeha             #+#    #+#             */
/*   Updated: 2024/08/25 17:15:59 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_object	*hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_hit_record	temp_rec;

	temp_rec = *rec;
	temp_rec.object = NULL;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			temp_rec.tmax = temp_rec.t;
			temp_rec.object = world;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (temp_rec.object);
}

t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	if (world->type == CY)
		hit_result = hit_cylinder(world, ray, rec);
	if (world->type == PL)
		hit_result = hit_plane(world, ray, rec);
	if (world->type == CO)
		hit_result = hit_cone(world ,ray, rec);
	return (hit_result);
}
