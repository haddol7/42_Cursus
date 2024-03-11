/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:03:23 by daeha             #+#    #+#             */
/*   Updated: 2024/03/11 20:49:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"
#include "ft_printf.h"
#include "libft.h"

#define FDF_BUFFER_SIZE	(50000)

#define ERR_MLC "❌ System call error - malloc() ❌"
#define ERR_OPN "❌ System call error - open() ❌"
#define ERR_RD "❌ System call error - read() ❌"

#define ERR_M_SIZE "❌ Input error - format is not rectangular ❌"
#define ERR_M_VAL "❌ Input error - file has invalid value ❌"

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

void	fdf_error(char *s);
int		fdf_isspace(char ch);

#endif
