/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:51:06 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 15:46:45 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_point(t_proj *first, t_proj *last, t_line *l, double *color);
static void	put(t_img *img, int x_proj, int y_proj, int color);
static int	step(double *color, int s_color, int i);

void	put_line_to_image(t_img *img, t_proj t1, t_proj t2)
{
	t_line	l;
	double	color[3];
	int		dx;
	int		dy;
	int		p;

	set_point(&t1, &t2, &l, color);
	dx = t2.x_proj - t1.x_proj;
	dy = (t2.y_proj - t1.y_proj) * l.sign;
	p = 2 * dy - dx;
	while (t1.x_proj <= t2.x_proj)
	{
		if (l.slope == 0)
			put(img, t1.x_proj, t1.y_proj, step(color, t1.color, ++l.step));
		else
			put(img, t1.y_proj, t1.x_proj, step(color, t1.color, ++l.step));
		if (p >= 0)
		{
			p += 2 * (dy - dx);
			t1.y_proj += 1 * l.sign;
		}
		else
			p += 2 * dy;
		t1.x_proj++;
	}
}

static int	step(double *color, int s_color, int i)
{
	int	r;
	int	g;
	int	b;

	r = get_red(s_color);
	g = get_green(s_color);
	b = get_blue(s_color);
	s_color = ((int)(r + i * color[0]) << 16) | \
			((int)(g + i * color[1]) << 8) | \
			(int)(b + i * color[2]);
	return (s_color);
}

static void	put(t_img *img, int x_proj, int y_proj, int color)
{
	void	*img_addr;

	if (x_proj < 0 || y_proj < 0 || \
		x_proj + 1 > WINDOW_X_SIZE || y_proj + 1 > WINDOW_Y_SIZE)
		return ;
	img_addr = img->addr + img->bits_per_pixel / \
			8 * x_proj + img->line_size * y_proj;
	*(unsigned int *)img_addr = color;
}

static int	get_step_color(double *color, t_proj t1, t_proj t2)
{
	double	step;

	if (abs(t2.x_proj - t1.x_proj) > abs(t2.y_proj - t1.y_proj))
		step = abs(t2.x_proj - t1.x_proj);
	else
		step = abs(t2.y_proj - t1.y_proj);
	color[0] = (get_red(t2.color) - get_red(t1.color)) / step;
	color[1] = (get_green(t2.color) - get_green(t1.color)) / step;
	color[2] = (get_blue(t2.color) - get_blue(t1.color)) / step;
	return (t1.color);
}

static void	set_point(t_proj *t1, t_proj *t2, t_line *l, double *color)
{
	l->step = 0;
	l->slope = 0;
	l->sign = 1;
	if (t1->x_proj > t2->x_proj)
		swap_point(t1, t2);
	if (t1->y_proj > t2->y_proj)
		l->sign = -1;
	if (abs(t2->y_proj - t1->y_proj) > t2->x_proj - t1->x_proj)
	{
		l->slope = 1;
		fdf_swap(&t1->x_proj, &t1->y_proj);
		fdf_swap(&t2->x_proj, &t2->y_proj);
		if (t1->x_proj > t2->x_proj)
			swap_point(t1, t2);
	}
	t1->color = get_step_color(color, *t1, *t2);
}
