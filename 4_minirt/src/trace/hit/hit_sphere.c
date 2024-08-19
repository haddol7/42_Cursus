/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:30:07 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 16:48:09 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

t_color3	texture(t_point3 p, t_sphere *sp, t_texture texture)
{
	t_point3	o;
	double	theta;
	double	phi;
	int		u;
	int		v;
	void	*img_addr;
	int		img_color;

	o.x = p.x - sp->center.x;
	o.y = p.y - sp->center.y;
	o.z = p.z - sp->center.z;

	theta = acos(-o.y / sp->radius);
	phi = atan2(-o.z, o.x) + M_PI;

	u = (phi / (2 * M_PI)) * texture.width;
	v = (1 - (theta / (M_PI))) * texture.height;
	img_addr = texture.img.addr + texture.img.bits_per_pixel / 8 * u + texture.img.line_size * v;
	img_color = *(unsigned int *)img_addr;
	return (vec3((double)((img_color & 0xff0000) >> 16 ) / 255.999, (double)((img_color & 0x00ff00) >> 8) / 255.999, (double)(img_color & 0x0000ff) / 255.999));
}

t_color3	texture_checkerboard(t_point3 p, t_sphere *sp)
{
	t_point3	o;
	double	theta;
	double	phi;
	double	u;
	double	v;

	o.x = p.x - sp->center.x;
	o.y = p.y - sp->center.y;
	o.z = p.z - sp->center.z;
	theta = acos(-o.y / sp->radius);
	phi = atan2(-o.z, o.x) + M_PI;
	u = phi / (2 * M_PI);
	v = theta / (M_PI);
	if (((int)(floor(u * 10)) + (int)floor(v * 10)) % 2 == 0)
		return vec3(0, 0, 0);
	else
		return vec3(1, 1, 1);
}

t_vec3 bump_mapping(t_hit_record *rec, t_sphere *sp, t_texture bump)
{
	t_point3	o;
	double	theta;
	double	phi;
	int		u;
	int		v;
	void	*img_addr;
	int		img_color;
	t_point3	p;
	t_vec3		v_w;
	
	p = rec->p;
	o.x = p.x - sp->center.x;
	o.y = p.y - sp->center.y;
	o.z = p.z - sp->center.z;

	theta = acos(-o.y / sp->radius);
	phi = atan2(-o.z, o.x) + M_PI;

	u = (phi / (2 * M_PI)) * bump.width;
	v = (1 - (theta / (M_PI))) * bump.height;
	img_addr = bump.img.addr + bump.img.bits_per_pixel / 8 * u + bump.img.line_size * v;
	img_color = *(unsigned int *)img_addr;
	
	double x = (double)(((img_color & 0xff0000) >> 16) - 128) / 128;
	double y = (double)(((img_color & 0x00ff00) >> 8) - 128) / 128;
	double z = (double)(((img_color & 0x0000ff)) - 128) / 128;
	
	t_vec3	T;
	t_vec3	B;
	t_vec3	N;
	//dprintf(2, "(%f,%f,%f)", rec->normal.x, rec->normal.y, rec->normal.z);
	N = rec->normal;
	T = vunit(vcross(vec3(0, 1, 0), N));
	B = vunit(vcross(N, T));
	v_w = vplus(vplus(vmult(T, x), vmult(B, y)), vmult(N, z));
	return (v_w);
}
//V_world = T * V_tangent.x + B * V_tangent.y + N * V_tangent.z

t_bool hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
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
	
    if (discriminant < 0)
		return (FALSE);
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
	if (sp_obj->bump.img.id)
		rec->normal = bump_mapping(rec, sp, sp_obj->bump);
	if (sp_obj->is_checker)
		rec->albedo = texture_checkerboard(rec->p, sp);
	else if (sp_obj->texture.img.id)
		rec->albedo = texture(rec->p, sp, sp_obj->texture);
	else
		rec->albedo = sp_obj->albedo;
	return (TRUE);
}
