#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdlib.h>
# include <mlx.h>

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;

typedef struct s_ray t_ray;

typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_scene t_scene;

typedef struct s_hit_record t_hit_record;
typedef struct s_object t_object;
typedef struct s_sphere t_sphere;
typedef struct s_light	t_light;
typedef struct s_img	t_img;
typedef struct s_mlx	t_mlx;
typedef struct s_data	t_data;

typedef int	t_bool;

# define FALSE 			0
# define TRUE 			1

typedef int	t_object_type;

# define SP 			0
# define LIGHT_POINT	1
# define LUMEN 			3

# define EPSILON 		1e-6 //0.000001

# define WINDOW_W		500
# define WINDOW_H		400
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
	double		viewport_h;
	double		viewport_w;
	t_vec3		vertical;
	t_vec3		horizontal;
	double		focal_len;
	t_point3	left_bottom;
	int			samples_per_pixel;
	double		vfov;
	t_point3	lookfrom;
	t_point3	lookat;
	t_vec3		vup;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
};

struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
};

struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
	t_color3	albedo;
};

struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
};

struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct s_light
{
	t_point3	origin;
	t_color3	light_color;
	double		bright_ratio;
};

struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color3		albedo;
};

struct s_img
{
	void	*id;
	void	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*img;
};

struct s_data
{
	t_mlx	*engine;
	t_scene	*scene;
};

#endif
