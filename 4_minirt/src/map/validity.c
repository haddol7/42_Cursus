/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:08:04 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/06 21:50:52 by jungslee         ###   ########.fr       */
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

void    map_validity(int fd)
{
    char	*buf;
    
}

void    error_exit(void)
{
    write(1, "Error\n", 6);
    exit(1);
}