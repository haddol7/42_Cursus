/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:27:39 by daeha             #+#    #+#             */
/*   Updated: 2024/09/09 20:42:00 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_BONUS_H
# define MAP_BONUS_H

# include "structures_bonus.h"
# include "scene_bonus.h"
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

void		free_split(char **split);
int			count_split_words(char **split);
t_point3	check_coordinate(char *coor);
t_vec3		check_normalize_vector(char *coor);
t_color3	check_color(char *color);
void		error_exit(char *str);
int			argument_validity(int argc, char *file_name);
void		map_validity(int fd, t_scene *scene, int *count, t_mlx *engine);
double		ft_atof(char *num);
void		free_split(char **split);
int			is_in_valid_normalize_range(double x, double y, double z);
int			is_color_in_valid_range(double r, double g, double b);
int			is_valid_ratio_range(double ratio);
void		object_normal(t_object *object, char *str, t_mlx engine);
t_object	*is_valid_sp(char **split, t_mlx engine);
t_object	*is_valid_cy(char **split, t_mlx engine);
t_object	*is_valid_pl(char **split, t_mlx engine);
t_object	*is_valid_a(char **split, t_scene *scene);
t_object	*is_valid_c(char **split, t_scene *scene, t_mlx *engine);
t_object	*is_valid_l(char **split, t_scene *scene);
t_object	*is_valid_co(char **split, t_mlx engine);

#endif
