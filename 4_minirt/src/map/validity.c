/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:08:04 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/08 22:30:40 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

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

int what_type(char *type)
{
    int len;
    static int  num_A = 0;
    static int  num_C = 0;
    static int  num_L = 0;//TODO 일단

    len = ft_strlen(type);
    if (!ft_strncmp(type, "sp", len) && !ft_strncmp(type, "sp", 2))
        return (SP);
    else if (!ft_strncmp(type, "cy", len) && !ft_strncmp(type, "cy", 2))
        return (CY);
    else if (!ft_strncmp(type, "pl", len) && !ft_strncmp(type, "pl", 2))
        return (PL);
    else if (!ft_strncmp(type, "A", len) && !ft_strncmp(type, "A", 1))
        return (AMBIENT);
    else if (!ft_strncmp(type, "C", len) && !ft_strncmp(type, "C", 1))
        return (CAMERA);
    else if (!ft_strncmp(type, "L", len) && !ft_strncmp(type, "L", 1))
        return (LIGHT);
    else
        error_exit();
}

void	*detect_element(char *line)
{
	int	i;
    char    **split;
    // t_object_type type;

	i = 0;
    split = ft_split(line, ' ');
    type = what_type(split[0])// 여기서 검증 먼저 하자.
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
    double      ka;

    line = NULL;
    while (1)
    {
        line = get_next_line(fd);
		if (line == 0)
			break ;
		detect_element(line);
		free(line);
    }
}

void    error_exit(void)
{
    write(1, "Error\n", 6);
    exit(1);
}