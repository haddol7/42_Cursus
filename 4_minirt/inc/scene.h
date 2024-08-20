/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:08:32 by daeha             #+#    #+#             */
/*   Updated: 2024/08/20 15:10:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

# define X 0
# define Y 1
# define Z 2

t_canvas	canvas(int width, int height);
t_camera	camera(t_scene *scene, t_mlx engine);
t_object	*object_default(t_object_type type, void *elem, t_color3 albedo);
t_object	*object_texture(t_object_type type, void *e, char *t, void *mlx);
t_sphere	*sphere(t_point3 center, double radius);
t_cylinder	*cylinder(t_point3 center, t_vec3 normal, double radius, double h);
t_plane		*plane(t_point3 center, t_vec3 normal);
t_light		*light_point(t_point3 origin, t_color3 color, double bright_ratio);

#endif
