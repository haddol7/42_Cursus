/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:28:15 by daeha             #+#    #+#             */
/*   Updated: 2024/03/16 16:00:11 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void pixel_put_to_image(t_img *img, int x_proj, int y_proj, int color)
{
	void	*img_addr;

	img_addr = img->addr + img->bits_per_pixel / 8 * x_proj + img->line_size * y_proj;
	*(unsigned int *)img_addr = color;
}

static int is_slope_bigger_than_one(t_point *first, t_point *last, int *minus)
{
	int	dx;
	int	dy;

	dx = first->x_proj - last->x_proj;
	dy = first->y_proj - last->y_proj;
	*minus = 1;
	if (dx * dy < 0)
		*minus = -1;
	if (abs(dy) > abs(dx))
	{
		fdf_swap(&first->x_proj, &first->y_proj);
		fdf_swap(&last->x_proj, &last->y_proj);
		if (*minus == -1)
		{
			fdf_swap(&first->x_proj, &last->x_proj);
			fdf_swap(&first->y_proj, &last->y_proj);
		}
		return (1);
	}
	return (0);
}

void	put_line_to_image(t_img *img, t_point first, t_point last)
{
	int	dx;
	int	dy;
	int	is_swap;
	int	p;
	int	minus;

	is_swap = is_slope_bigger_than_one(&first, &last, &minus);
	dx = abs(first.x_proj - last.x_proj);
	dy = abs(first.y_proj - last.y_proj);
	p = (2 * dy - dx) * minus;
	if (first.x_proj >= last.x_proj)
	{
		fdf_swap(&first.x_proj, &last.x_proj);
		fdf_swap(&first.y_proj, &last.y_proj);
	}
	while (first.x_proj++ < last.x_proj)
	{
		if (is_swap)
			pixel_put_to_image(img, first.y_proj, first.x_proj, 0xffffff);
		else
			pixel_put_to_image(img, first.x_proj, first.y_proj, 0xffffff);
		if (p * minus >= 0)
		{
			p += (2 * dy - 2 * dx) * minus;
			first.y_proj += 1 * minus;
		}
		else
			p += 2 * dy * minus;
	}
}
