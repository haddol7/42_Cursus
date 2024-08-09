/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:08:04 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/09 19:54:42 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int    argument_validity(int argc, char *file_name)
{
    int fd;

    if (argc != 2)
        error_exit();
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        error_exit();
    return (fd);
}

int what_type(char **split)
{
    int len;
    static int  num_A = 0;
    static int  num_C = 0;
    static int  num_L = 0;//TODO 일단

    len = ft_strlen(split[0]);
    if (!ft_strncmp(split[0], "sp", len) && !ft_strncmp(split[0], "sp", 2))
        return (is_valid_sp(split));
    else if (!ft_strncmp(split[0], "cy", len) && !ft_strncmp(split[0], "cy", 2))
        return (is_valid_cy(split));
    else if (!ft_strncmp(split[0], "pl", len) && !ft_strncmp(split[0], "pl", 2))
        return (is_valid_pl(split));
    else if (!ft_strncmp(split[0], "A", len) && !ft_strncmp(split[0], "A", 1))
        return (is_valid_A(split));
    else if (!ft_strncmp(split[0], "C", len) && !ft_strncmp(split[0], "C", 1))
        return (is_valid_C(split));
    else if (!ft_strncmp(split[0], "L", len) && !ft_strncmp(split[0], "L", 1))
        return (is_valid_L(split));
    else
        error_exit();
}

void	*create_object(char *line)
{
	int	i;
    char    **split;
    t_object    *new_object;
    // t_object_type type;

	i = 0;
    split = ft_split(line, ' ');
    new_object = what_type(split);// 여기서 검증 먼저 하자.
    // if ()
    //free!!!
    // for (int i = 0; split[i] != NULL; i++)
    // {
    //     printf("%s", split[i]);
    // }
    // type = what_type(line + i, &i);
    // if (type == SP)
    // else if (type == CY)

    // else if (type == PL)

    // else if (type == LIGHT)

    // else if (type == AMBIENT)

    // else if (type == CAMERA)
        
}

void    map_validity(int fd, t_scene *scene)
{
    char	*line;
    t_object    *world;
    t_object    *light;
    t_object    *new_object;
    double      ka;

    line = NULL;
    while (1)
    {
        line = get_next_line(fd);
		if (line == 0)
			break ;
        new_object = create_object(line);
// oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
		oadd(&world, new_object);
        free(line);
    }
}

void    error_exit(void)
{
    write(1, "Error\n", 6);
    exit(1);
}