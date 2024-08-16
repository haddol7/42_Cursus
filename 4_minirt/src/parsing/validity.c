/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:08:04 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/16 16:47:42 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

int    argument_validity(int argc, char *file_name)
{
    int fd;

    if (argc != 2)
        error_exit("argument_validity : 1\n");
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        error_exit("argment_validity : 2\n");
    return (fd);
}

t_object	*what_type(char **split, t_scene *scene)
{
	int len;

	len = ft_strlen(split[0]);
	if (!ft_strncmp(split[0], "sp", len) && !ft_strncmp(split[0], "sp", 2))
		return (is_valid_sp(split));
	else if (!ft_strncmp(split[0], "cy", len) && !ft_strncmp(split[0], "cy", 2))
		return (is_valid_cy(split));
	else if (!ft_strncmp(split[0], "pl", len) && !ft_strncmp(split[0], "pl", 2))
		return (is_valid_pl(split));
	else if (!ft_strncmp(split[0], "A", len) && !ft_strncmp(split[0], "A", 1))
		return (is_valid_A(split, scene));
	else if (!ft_strncmp(split[0], "C", len) && !ft_strncmp(split[0], "C", 1))
		return (is_valid_C(split, scene));
	else if (!ft_strncmp(split[0], "L", len) && !ft_strncmp(split[0], "L", 1))
		return (is_valid_L(split, scene));
	else
		error_exit("what_type\n");
	return (0);
}

void	*create_object(char *line, t_scene *scene)
{
    char    **split;
    t_object    *new_object;

    split = ft_split(line, ' ');
    new_object = what_type(split, scene);// 여기서 검증 먼저 하자.
	free_split(split);
	return (new_object);
}

void    map_validity(int fd, t_scene *scene, int *capital_ob)
{
	char		*line;
	t_object    *world;
	t_object    *new_object;

	line = NULL;
	world = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		new_object = create_object(line, scene);
		if (new_object != NULL)
			oadd(&world, new_object);
		else
			(*capital_ob)++;
		free(line);
	}
	scene->world = world;
}

void    error_exit(char *str)
{
    write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
    exit(1);
}