/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:28:15 by daeha             #+#    #+#             */
/*   Updated: 2024/03/15 20:35:59 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void pixel_put_to_image(t_img *img, int x, int y, int color)
{
	void	*img_addr;

	img_addr = img->addr + img->bits_per_pixel / 8 * x + img->line_size * y;
	*(unsigned int *)img_addr = color;
}

static int is_slope_bigger_than_one(t_point *first, t_point *last, int *minus)
{
	int	dx;
	int	dy;

	dx = first->x - last->x;
	dy = first->y - last->y;
	*minus = 1;
	if (dx * dy < 0)
		*minus = -1;
	if (abs(dy) > abs(dx))
	{
		fdf_swap(&first->x, &first->y);
		fdf_swap(&last->x, &last->y);
		if (*minus == -1)
		{
			fdf_swap(&first->x, &last->x);
			fdf_swap(&first->y, &last->y);
		}
		return (1);
	}
	return (0);
}

void	put_line_to_image(t_img *img, t_point first, t_point last, int color)
{
	int	dx;
	int	dy;
	int	is_swap;
	int	p;
	int	minus;

	is_swap = is_slope_bigger_than_one(&first, &last, &minus);
	dx = abs(first.x - last.x);
	dy = abs(first.y - last.y);
	p = (2 * dy - dx) * minus;
	if (first.x >= last.x)
	{
		fdf_swap(&first.x, &last.x);
		fdf_swap(&first.y, &last.y);
	}
	while (first.x++ < last.x)
	{
		if (is_swap)
			pixel_put_to_image(img, first.y, first.x, color);
		else
			pixel_put_to_image(img, first.x, first.y, color);
		if (p * minus >= 0)
		{
			p += (2 * dy - 2 * dx) * minus;
			first.y += 1 * minus;
		}
		else
			p += 2 * dy * minus;
	}
}
