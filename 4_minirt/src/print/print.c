/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:33 by daeha             #+#    #+#             */
/*   Updated: 2024/08/16 15:37:35 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "utils.h"

void write_color(t_img *img, t_color3 pixel_color, int x, int y)
{
	void	*img_addr;
	
	img_addr = img->addr + img->bits_per_pixel / 8 * x + img->line_size * y;
	*(unsigned int *)img_addr = ((int)(255.999 * pixel_color.x / ANTI_SAMPLE) << 16) | \
								((int)(255.999 * pixel_color.y / ANTI_SAMPLE) << 8) | \
								(int)(255.999 * pixel_color.z / ANTI_SAMPLE);
}
