/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:30:28 by daeha             #+#    #+#             */
/*   Updated: 2024/09/09 20:22:48 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures_bonus.h"
#include "utils_bonus.h"
#include "trace_bonus.h"

static t_vec3	bump_normal_vector(int img_color, t_hit_record *rec);

t_color3	texture(t_object *obj, t_texture *tex, t_hit_record *rec)
{
	double		uv[2];
	void		*img_addr;
	int			img_color;

	uv_mapping(uv, obj, tex, rec);
	img_addr = tex->img.addr + tex->img.bits_per_pixel / 8 * (int)uv[U] \
				+ tex->img.line_size * (int)uv[V];
	img_color = *(unsigned int *)img_addr;
	return (vec3((double)((img_color & 0xff0000) >> 16) / 255.999, \
				(double)((img_color & 0x00ff00) >> 8) / 255.999, \
				(double)(img_color & 0x0000ff) / 255.999));
}

t_vec3	bump(t_object *obj, t_texture *bump, t_hit_record *rec)
{
	double		uv[2];
	void		*img_addr;
	int			img_color;

	uv_mapping(uv, obj, bump, rec);
	img_addr = bump->img.addr + bump->img.bits_per_pixel / 8 * (int)uv[U] \
				+ bump->img.line_size * (int)uv[V];
	img_color = *(unsigned int *)img_addr;
	return (bump_normal_vector(img_color, rec));
}

t_color3	checkerboard(t_object *obj, t_hit_record *rec)
{
	double		uv[2];

	uv_mapping(uv, obj, NULL, rec);
	if (((int)(floor(uv[U] * 10)) + (int)floor(uv[V] * 10)) % 2 == 0)
		return (vec3(0, 0, 0));
	else
		return (vec3(1, 1, 1));
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
