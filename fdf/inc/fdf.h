/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:03:23 by daeha             #+#    #+#             */
/*   Updated: 2024/03/05 20:34:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <fcntl.h>

typedef struct	s_point
{
	int	x;
	int y;
	int z;
}	t_point;

typedef struct	s_map
{
	t_point	*data;
	t_point angular;
	size_t	x_size;
	size_t	y_size;
}	t_map;

typedef struct	s_file
{
	char	*data;
	t_file	*next;
}	t_file;

#endif
