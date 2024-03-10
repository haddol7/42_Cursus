/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:03:23 by daeha             #+#    #+#             */
/*   Updated: 2024/03/10 21:41:06 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include "mlx.h"
#include "ft_printf.h"
#include "libft.h"

#define FDF_BUFFER_SIZE	(500000)
typedef struct	s_point
{
	int	x;
	int y;
	int z;
	int	color;
}	t_point;

typedef struct	s_map
{
	t_point	*data;
	t_point angular;
	size_t	x_size;
	size_t	y_size;
}	t_map;

#endif
