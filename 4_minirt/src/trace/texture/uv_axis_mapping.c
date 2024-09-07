/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_axis_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:43:17 by daeha             #+#    #+#             */
/*   Updated: 2024/09/07 15:43:34 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

t_vec3	uv_axis_mapping(t_point3 center, t_vec3 normal, t_hit_record *rec)
{
	t_vec3		p;
	double		theta;
	t_vec3		axis;
	t_vec3		y_axis;

	p = vminus(rec->p, center);
	y_axis = vec3(0, 1, 0);
	axis = vunit(vcross(y_axis, normal));
	theta = acos(vdot(y_axis, normal));
	rotation(&p, axis, -theta * 180 / M_PI);
	return (p);
}
