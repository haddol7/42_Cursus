/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:27:39 by daeha             #+#    #+#             */
/*   Updated: 2024/08/21 11:32:23 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "structures.h"
# include "scene.h"
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_num
{
	int		dot_flag;
	double	sign;
	double	mult;
}	t_num;

void		error_exit(char *str);
int			argument_validity(int argc, char *file_name);
void		map_validity(int fd, t_scene *scene, int *count, t_mlx *engine);
double		ft_atof(char *num);
void		free_split(char **split);
t_object	*is_valid_sp(char **split, t_mlx engine);
t_object	*is_valid_cy(char **split, t_mlx engine);
t_object	*is_valid_pl(char **split, t_mlx engine);
t_object	*is_valid_A(char **split, t_scene *scene);
t_object	*is_valid_C(char **split, t_scene *scene, t_mlx *engine);
t_object	*is_valid_L(char **split, t_scene *scene);
t_object	*is_valid_co(char **split, t_mlx engine);

#endif
