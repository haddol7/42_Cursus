/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:22 by daeha             #+#    #+#             */
/*   Updated: 2024/08/16 15:59:08 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_canvas canvas(int width, int height)
{
	t_canvas canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

void rotation(t_vec3 *v, t_vec3 axis, double theta)
{
	double	cosine;
	double	sine;
	double	onecos;
	t_vec3	ret;
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;

	cosine = cos(theta * (M_PI) / 180);
	sine = sin(theta * (M_PI) / 180);
	onecos = 1 - cosine;
	x.x = cosine + axis.x * axis.x * onecos;
	x.y = axis.x * axis.y * onecos - axis.z * sine;
	x.z = axis.x * axis.z * onecos + axis.y * sine;
	y.x = axis.y * axis.x * onecos + axis.z * sine;
	y.y = cosine + axis.y * axis.y * onecos;
	y.z = axis.y * axis.z * onecos - axis.x * sine;
	z.x = axis.z * axis.x * onecos - axis.y * sine;
	z.y = axis.z * axis.y * onecos + axis.x * sine;
	z.z = cosine + axis.z * axis.z * onecos;
	
	ret.x = v->x * x.x + v->y * x.y + v->z * x.z;
	ret.y = v->x * y.x + v->y * y.y + v->z * y.z;
	ret.z = v->x * z.x + v->y * z.y + v->z * z.z;
	*v = ret;
}

t_camera    camera(t_canvas *canvas, t_mlx engine)
{
    t_camera    cam;
    double      viewport_height;
	double		theta;

	cam.lookfrom = engine.trans;
	cam.lookat = vplus(engine.trans, point3(0, 0, -1));
	cam.vup = vec3(0, 1, 0);
    cam.focal_len = vlength(vminus(cam.lookfrom, cam.lookat));
	
	cam.vfov = engine.fov;

	theta = cam.vfov * (M_PI) / 180;
    viewport_height = tan(theta / 2) * 2 * cam.focal_len;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.viewport_h = viewport_height;

	cam.w = vunit(vminus(cam.lookfrom, cam.lookat));
	rotation(&cam.vup, vec3(0, 0, -1), engine.rotate.z);
	rotation(&cam.w, vunit(vcross(cam.vup, cam.w)), engine.rotate.x);
	rotation(&cam.w, vec3(0, -1, 0), engine.rotate.y);
	cam.u = vunit(vcross(cam.vup, cam.w));
	cam.v = vcross(cam.w, cam.u);
    cam.orig = cam.lookfrom;
    
	cam.horizontal = vmult(cam.u, cam.viewport_w);
    cam.vertical = vmult(cam.v, cam.viewport_h);
    cam.left_bottom = vminus(vminus(cam.orig, vmult(cam.w, cam.focal_len)), vplus(vdivide(cam.vertical, 2), vdivide(cam.horizontal, 2)));
	cam.samples_per_pixel = ANTI_SAMPLE;
    return (cam);
}
