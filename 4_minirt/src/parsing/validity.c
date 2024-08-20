/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:08:04 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/20 15:21:49 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	argument_validity(int argc, char *file_name)
{
	int	fd;

	if (argc != 2)
		error_exit("argument_validity : 1\n");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_exit("argment_validity : 2\n");
	return (fd);
}

t_object	*what_type(char **split, t_scene *scene, t_mlx *engine)
{
	int	len;

	len = ft_strlen(split[0]);
	if (!ft_strncmp(split[0], "sp", len) && !ft_strncmp(split[0], "sp", 2))
		return (is_valid_sp(split, *engine));
	else if (!ft_strncmp(split[0], "cy", len) && !ft_strncmp(split[0], "cy", 2))
		return (is_valid_cy(split, *engine));
	else if (!ft_strncmp(split[0], "pl", len) && !ft_strncmp(split[0], "pl", 2))
		return (is_valid_pl(split, *engine));
	else if (!ft_strncmp(split[0], "A", len) && !ft_strncmp(split[0], "A", 1))
		return (is_valid_A(split, scene));
	else if (!ft_strncmp(split[0], "C", len) && !ft_strncmp(split[0], "C", 1))
		return (is_valid_C(split, scene, engine));
	else if (!ft_strncmp(split[0], "L", len) && !ft_strncmp(split[0], "L", 1))
		return (is_valid_L(split, scene));
	else
		error_exit("what_type\n");
	return (0);
}

void	*create_object(char *line, t_scene *scene, t_mlx *engine, int *none)
{
	t_object	*new_object;
	char		**split;

	new_object = 0;
	split = ft_split(line, ' ');
	if (split[0] == NULL || split[0][0] == '\0' || split[0][0] == '\n')
		*none = 1;
	else
		new_object = what_type(split, scene, engine);// 여기서 검증 먼저 하자.
	free_split(split);
	return (new_object);
}

void	map_validity(int fd, t_scene *scene, int *capital_ob, t_mlx *engine)
{
	t_object	*world;
	t_object	*new_object;
	char		*line;
	int			none;

	line = NULL;
	world = NULL;
	while (1)
	{
		none = 0;
		line = get_next_line(fd);
		if (line == 0)
			break ;
		new_object = create_object(line, scene, engine, &none);
		if (new_object != NULL)
			oadd(&world, new_object);
		else if (none == 0)
			(*capital_ob)++;
		free(line);
	}
	scene->world = world;
}

void	error_exit(char *str)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}
