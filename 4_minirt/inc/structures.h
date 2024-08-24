/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:27:28 by daeha             #+#    #+#             */
/*   Updated: 2024/08/24 16:19:14 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdlib.h>
# include <mlx.h>

typedef int						t_bool;
typedef int						t_object_type;

typedef struct s_vec3			t_vec3;
typedef struct s_vec3			t_point3;
typedef struct s_vec3			t_color3;

typedef struct s_ray			t_ray;

typedef struct s_camera			t_camera;
typedef struct s_canvas			t_canvas;
typedef struct s_scene			t_scene;

typedef struct s_hit_record		t_hit_record;
typedef struct s_texture		t_texture;
typedef struct s_object			t_object;
typedef struct s_sphere			t_sphere;
typedef struct s_cylinder		t_cylinder;
typedef struct s_plane			t_plane;
typedef struct s_light			t_light;
typedef struct s_cone			t_cone;
typedef struct s_img			t_img;
typedef struct s_mlx			t_mlx;
typedef struct s_data			t_data;
typedef struct s_discriminant	t_discriminant;

# define FALSE 			0
# define TRUE 			1

# define SP 			0
# define CY 			1
# define PL				2
# define LIGHT			3
# define AMBIENT		4
# define CAMERA			5
# define CO				6

# define LIGHT_POINT	6
# define LUMEN 			3

# define EPSILON 		1e-6

# define WINDOW_W		1080
# define WINDOW_H		800
# define ANTI_SAMPLE	1

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct s_camera
{
	t_point3	orig;
	double		vfov;
	t_vec3		vup;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
	t_vec3		vertical;
	t_vec3		horizontal;
	double		viewport_h;
	double		viewport_w;
	t_point3	left_bottom;
	int			samples_per_pixel;
};

struct s_canvas
{
	int		w;
	int		h;
	double	aspect_ratio;
};

struct s_hit_record
{
	t_object	*object;
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
	t_color3	albedo;
	double		u;
	double		v;
};

struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_object		*selected_obj;
	t_color3		ambient;
	double			ka;
	t_ray			ray;
	t_hit_record	rec;
};

struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct s_cylinder
{
	t_point3	center;
	double		radius;
	double		radius2;
	double		height;
	t_vec3		normal;
};

struct s_cone
{
	t_point3	center;
	double		radius;
	double		radius2;
	t_point3	cross;
	t_vec3		normalize;
};


struct s_plane
{
	t_point3	center;
	t_vec3		normal;
};

struct s_light
{
	t_point3	origin;
	t_color3	light_color;
	double		bright_ratio;
};

struct s_img
{
	void	*id;
	void	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
};

struct s_texture
{	
	int		type;
	t_img	img;
	int		width;
	int		height;
};

struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_bool			is_checker;
	t_texture		texture;
	t_texture		bump;
	t_color3		albedo;
};

struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_vec3		mouse;
	t_vec3		mouse_delta;
	t_point3	trans;
	t_vec3		rotate;
	double		fov;
};

struct s_data
{
	t_mlx		*engine;
	t_scene		*scene;
};

struct s_discriminant
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	sqrtd;
};


#endif
