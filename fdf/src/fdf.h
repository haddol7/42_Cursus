/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:03:23 by daeha             #+#    #+#             */
/*   Updated: 2024/03/16 14:48:59 by daeha            ###   ########.fr       */
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

typedef struct	s_point
{
	int	x;
	int y;
	int z;
	int	color;
}	t_point;

typedef struct s_plain
{
	int x;
	int y;
	int color;
}	t_plain;

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
	t_point	*data;
	t_plain *data_proj;
	t_point	translate;
	t_point angular;
	size_t	col;
	size_t	row;
}	t_map;

typedef struct s_client
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
}	t_client;

void	fdf_swap(int *a, int *b);
void	fdf_error(char *s);
int		fdf_isspace(char ch);
void	load_map(char *dir, t_map *map);
void	put_line_to_image(t_img *img, t_point first, t_point last, int color);

#endif
