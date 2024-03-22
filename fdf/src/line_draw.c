/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:51:06 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 15:19:47 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_line_info(t_point_proj *first, t_point_proj *last, t_line *l, double *color);
static void pixel_put_to_image(t_img *img, int x_proj, int y_proj, int color);
static int	set_color(double *color, t_point_proj first, t_point_proj last);
static int	get_color(double *color, int s_color, int i);

void	put_line_to_image(t_img *img, t_point_proj first, t_point_proj last)
{
	t_line	l;
	double	color[3];
	int	dx;
	int	dy;
	int	p;

	init_line_info(&first, &last, &l, color);
	dx = last.x_proj - first.x_proj;
	dy = (last.y_proj - first.y_proj) * l.sign;
	p = 2 * dy - dx;
	while (first.x_proj <= last.x_proj)
	{
		if (l.slope == 0)
			pixel_put_to_image(img, first.x_proj, first.y_proj, get_color(color, first.color, ++l.step));
		else
			pixel_put_to_image(img, first.y_proj, first.x_proj, get_color(color, first.color, ++l.step));
		if (p >= 0)
		{
			p += 2 * (dy - dx);
			first.y_proj += 1 * l.sign;
		}
		else
			p += 2 * dy;
		first.x_proj++;
	}
}

static int	get_color(double *color, int s_color, int i)
{
	int r;
	int g;
	int b;

	r = get_red(s_color);
	g = get_green(s_color);
	b = get_blue(s_color);
	s_color = ((int)(r + i * color[0]) << 16) | ((int)(g + i * color[1]) << 8) | (int)(b + i * color[2]);
	return (s_color);
}

static void pixel_put_to_image(t_img *img, int x_proj, int y_proj, int color)
{
	void	*img_addr;
	
	if (x_proj < 0 || y_proj < 0 || x_proj + 1 > WINDOW_X_SIZE || y_proj + 1 > WINDOW_Y_SIZE)
		return ;

	img_addr = img->addr + img->bits_per_pixel / 8 * x_proj + img->line_size * y_proj;
	*(unsigned int *)img_addr = color;
}

static int set_color(double *color, t_point_proj first, t_point_proj last)
{
	double step;

	if (abs(last.x_proj - first.x_proj) > abs(last.y_proj - first.y_proj))
		step = abs(last.x_proj - first.x_proj);
	else
		step = abs(last.y_proj - first.y_proj);
	color[0] = (get_red(last.color) - get_red(first.color)) / step;
	color[1] = (get_green(last.color) - get_green(first.color)) / step;
	color[2] = (get_blue(last.color) - get_blue(first.color)) / step;
	return (first.color);
}

static void	init_line_info(t_point_proj *first, t_point_proj *last, t_line *l, double *color)
{
	l->step = 0;
	l->slope = 0;
	l->sign = 1;
	if (first->x_proj > last->x_proj)
		swap_point(first, last);
	if (first->y_proj > last->y_proj)
		l->sign = -1;
	if (abs(last->y_proj - first->y_proj) > last->x_proj - first->x_proj)
	{
		l->slope = 1;
		fdf_swap(&first->x_proj, &first->y_proj);
		fdf_swap(&last->x_proj, &last->y_proj);
		if (first->x_proj > last->x_proj)
			swap_point(first, last);
	}
	first->color = set_color(color, *first, *last);
}
