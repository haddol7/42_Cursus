/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:45:36 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 15:19:43 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int get_red(int color)
{
	return ((color & 0xff0000) >> 16);
}
int get_green(int color)
{
	return ((color & 0x00ff00) >> 8);
}
int get_blue(int color)
{
	return (color & 0x0000ff);
}
