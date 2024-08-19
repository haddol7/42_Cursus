/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:31:49 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 21:33:34 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

static t_vec3	bump_normal_vector(int img_color, t_hit_record *rec);

void	uv_mapping_sp(int uv[2], t_point3 p, t_sphere *sp, t_texture *t)
{
	t_point3	o;
	double		theta;
	double		phi;

	o.x = p.x - sp->center.x;
	o.y = p.y - sp->center.y;
	o.z = p.z - sp->center.z;
	theta = acos(-o.y / sp->radius);
	phi = atan2(-o.z, o.x) + M_PI;
	if (t == NULL)
	{
		uv[U] = (phi / (2 * M_PI));
		uv[V] = (1 - (theta / (M_PI)));
	}
	else
	{
		uv[U] = (phi / (2 * M_PI)) * t->width;
		uv[V] = (1 - (theta / (M_PI))) * t->height;
	}
}

t_color3	texture(t_point3 p, t_sphere *sp, t_texture texture)
{
	int			uv[2];
	void		*img_addr;
	int			img_color;

	uv_mapping_sp(uv, p, sp, &texture);
	img_addr = texture.img.addr + texture.img.bits_per_pixel / 8 * uv[U] \
				+ texture.img.line_size * uv[V];
	img_color = *(unsigned int *)img_addr;
	return (vec3((double)((img_color & 0xff0000) >> 16) / 255.999, \
				(double)((img_color & 0x00ff00) >> 8) / 255.999, \
				(double)(img_color & 0x0000ff) / 255.999));
}

t_color3	texture_checkerboard(t_point3 p, t_sphere *sp)
{
	int			uv[2];

	uv_mapping_sp(uv, p, sp, NULL);
	if (((int)(floor(uv[U] * 10)) + (int)floor(uv[V] * 10)) % 2 == 0)
		return (vec3(0, 0, 0));
	else
		return (vec3(1, 1, 1));
}

t_vec3	bump_mapping(t_hit_record *rec, t_sphere *sp, t_texture bump)
{
	int			uv[2];
	void		*img_addr;
	int			img_color;
	t_point3	p;

	p = rec->p;
	uv_mapping_sp(uv, p, sp, &bump);
	img_addr = bump.img.addr + bump.img.bits_per_pixel / 8 * uv[U] \
				+ bump.img.line_size * uv[V];
	img_color = *(unsigned int *)img_addr;
	return (bump_normal_vector(img_color, rec));
}

static t_vec3	bump_normal_vector(int img_color, t_hit_record *rec)
{
	t_vec3	bump;
	t_vec3	t;
	t_vec3	b;
	t_vec3	n;

	bump.x = (double)(((img_color & 0xff0000) >> 16) - 128) / 128;
	bump.y = (double)(((img_color & 0x00ff00) >> 8) - 128) / 128;
	bump.z = (double)(((img_color & 0x0000ff)) - 128) / 128;
	n = rec->normal;
	t = vunit(vcross(vec3(0, 1, 0), n));
	b = vunit(vcross(n, t));
	return (vplus(vplus(vmult(t, bump.x), vmult(b, bump.y)), vmult(n, bump.z)));
}
