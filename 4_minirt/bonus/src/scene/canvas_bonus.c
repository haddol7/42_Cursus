/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:22 by daeha             #+#    #+#             */
/*   Updated: 2024/09/10 02:59:14 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"

t_canvas	canvas(int width, int height)
{
	t_canvas	canvas;

	canvas.w = width;
	canvas.h = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

void	rotation(t_vec3 *v, t_vec3 axis, double theta)
{
	double	cosine;
	double	sine;
	double	onecos;
	t_vec3	ret;
	t_vec3	local[3];

	cosine = cos(theta * (M_PI) / 180);
	sine = sin(theta * (M_PI) / 180);
	onecos = 1 - cosine;
	local[X].x = cosine + axis.x * axis.x * onecos;
	local[X].y = axis.x * axis.y * onecos - axis.z * sine;
	local[X].z = axis.x * axis.z * onecos + axis.y * sine;
	local[Y].x = axis.y * axis.x * onecos + axis.z * sine;
	local[Y].y = cosine + axis.y * axis.y * onecos;
	local[Y].z = axis.y * axis.z * onecos - axis.x * sine;
	local[Z].x = axis.z * axis.x * onecos - axis.y * sine;
	local[Z].y = axis.z * axis.y * onecos + axis.x * sine;
	local[Z].z = cosine + axis.z * axis.z * onecos;
	ret.x = v->x * local[X].x + v->y * local[X].y + v->z * local[X].z;
	ret.y = v->x * local[Y].x + v->y * local[Y].y + v->z * local[Y].z;
	ret.z = v->x * local[Z].x + v->y * local[Z].y + v->z * local[Z].z;
	*v = vunit(ret);
}

t_camera	camera(t_scene *scene, t_mlx engine)
{
	t_camera	cam;
	double		viewport_height;

	cam.orig = engine.trans;
	cam.vup = vec3(0, 1, 0);
	cam.vfov = engine.fov;
	viewport_height = tan(cam.vfov * (M_PI) / 360) * 2;
	cam.viewport_w = viewport_height * scene->canvas.aspect_ratio;
	cam.viewport_h = viewport_height;
	cam.w = vec3(0, 0, 1);
	rotation(&cam.vup, vec3(0, 0, -1), engine.rotate.z);
	rotation(&cam.w, vunit(vcross(cam.vup, cam.w)), \
			engine.rotate.x + engine.mouse_delta.y);
	rotation(&cam.w, vec3(0, -1, 0), engine.rotate.y + engine.mouse_delta.x);
	cam.u = vunit(vcross(cam.vup, cam.w));
	cam.v = vcross(cam.w, cam.u);
	cam.horizontal = vmult(cam.u, cam.viewport_w);
	cam.vertical = vmult(cam.v, cam.viewport_h);
	cam.left_bottom = vminus(vminus(cam.orig, vmult(cam.w, 1)), \
				vplus(vdivide(cam.vertical, 2), vdivide(cam.horizontal, 2)));
	cam.samples_per_pixel = ANTI_SAMPLE;
	return (cam);
}
