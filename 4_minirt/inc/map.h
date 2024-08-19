#ifndef MAP_H
# define MAP_H

# include "structures.h"
# include "scene.h"
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "../lib/libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_num
{
    double	sign;
	double	mult;
	int		dot_flag;
} t_num;


void	error_exit(char *str);
int		argument_validity(int argc, char *file_name);
void    map_validity(int fd, t_scene *scene, int *capital_ob, t_mlx engine);
double	ft_atof(char *num);
void	free_split(char **split);
t_object	*is_valid_sp(char **split, t_mlx engine);
t_object	*is_valid_cy(char **split, t_mlx engine);
t_object	*is_valid_pl(char **split, t_mlx engine);
t_object	*is_valid_A(char **split, t_scene *scene);
t_object	*is_valid_C(char **split, t_scene *scene);
t_object	*is_valid_L(char **split, t_scene *scene);

#endif