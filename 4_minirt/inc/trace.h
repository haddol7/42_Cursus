/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:36:03 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 21:38:15 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

# define U 0
# define V 0
# define KSN 64
# define KS  0.5

t_ray			ray(t_point3 orig, t_vec3 dir);
t_point3		ray_at(t_ray *ray, double t);
t_ray			ray_primary(t_camera *cam, double u, double v);
t_hit_record	record_init(void);
t_color3		ray_color(t_scene *scene, t_color3 color);
t_object		*hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool			hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_color3		texture(t_point3 p, t_sphere *sp, t_texture texture);
t_color3		texture_checkerboard(t_point3 p, t_sphere *sp);
t_bool			hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
void			set_face_normal(t_ray *r, t_hit_record *rec);
t_color3		phong_lighting(t_scene *scene);
t_color3		point_light_get(t_scene *scene, t_light *light);
void			uv_mapping_sp(int u[2], t_point3 p, t_sphere *s, t_texture *t);
t_color3		texture(t_point3 p, t_sphere *sp, t_texture texture);
t_color3		texture_checkerboard(t_point3 p, t_sphere *sp);
t_vec3			bump_mapping(t_hit_record *rec, t_sphere *sp, t_texture bump);

#endif
