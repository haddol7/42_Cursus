/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:15:44 by daeha             #+#    #+#             */
/*   Updated: 2024/01/11 18:40:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <stdlib.h>
#include <unistd.h>

typedef struct	s_fd_list
{
	int				fd;
	char			*buffer;
	struct s_list	*next;
} t_fd_list;

char	*get_next_line(int fd);
