/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:03:23 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 15:21:51 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"
#include "ft_printf.h"
#include "libft.h"


#define WINDOW_X_SIZE (1920)
#define WINDOW_Y_SIZE (1080)

#define FDF_BUFFER_SIZE	(50000)

#define ERR_MLX "❌ MLX error ❌"

#define ERR_ARGC "❌ Input error - argument size is not one ❌"
#define ERR_MLC "❌ System call error - malloc() ❌"
#define ERR_OPN "❌ System call error - open() ❌"
#define ERR_RD "❌ System call error - read() ❌"

#define ERR_M_SIZE "❌ Input error - format is not rectangular ❌"
#define ERR_M_VAL "❌ Input error - file has invalid value ❌"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17

#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_C			8

# define MOUSE_LEFT		1
# define MOUSE_RIGHT	2
# define MOUSE_MID		3
# define MOUSE_UP		4
# define MOUSE_DOWN		5

# define A		0
# define B		1
# define G		2

# define X		0
# define Y		1
# define Z		2

typedef struct	s_point
{
	int	x;
	int y;
	int z;
	int	color;
}	t_point;

typedef struct	s_point_proj
{
	int	x;
	int y;
	int z;
	int	x_proj;
	int y_proj;
	int	color;
}	t_point_proj;

typedef struct s_img
{
	void	*id;
	void	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img;

typedef struct	s_map
{
	t_point			*point;
	t_point_proj	*copy;
	t_point			translate;
	t_point 		angular;
	double			scale;
	size_t			col;
	size_t			row;
}	t_map;

typedef struct s_line
{
	int	slope;
	int	sign;
	int	step;
}	 t_line;

typedef struct s_mouse
{
	int	is_pressed;
	int	x;
	int	y;
}	t_mouse;

typedef struct s_client
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	img;
	t_mouse	mouse;
}	t_client;

//color.c
int 	get_red(int color);
int 	get_green(int color);
int 	get_blue(int color);

//line_draw.c
void	put_line_to_image(t_img *img, t_point_proj first, t_point_proj last);

//map_load.c
void	load_map(char *dir, t_client *data);

//map_load_utils.c
int		check_map_value(char **s, int *color);
int		check_map_color(char **s);

//map_conv.c
void 	translate(t_point_proj *point, t_point trans, size_t size);
void 	rotate(t_map *map, size_t size);

//map_draw.c
void 	draw(t_map map, t_img *img, void *mlx, void *win);

//utils.c
void 	fdf_swap(int *a, int *b);
void 	swap_point(t_point_proj *first, t_point_proj *last);
void	fdf_error(char *msg);
int		fdf_isspace(char ch);

#endif
