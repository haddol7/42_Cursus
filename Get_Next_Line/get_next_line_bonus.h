/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:48:15 by daeha             #+#    #+#             */
/*   Updated: 2024/01/17 21:59:15 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

typedef struct	s_fd_list
{
	int					fd;
	char				*buffer;
	size_t				buf_size;
	size_t				len;
	struct s_fd_list	*head;
	struct s_fd_list	*next;
} t_fd_list;


char	*get_next_line(int fd);
int		find_fd(int fd, t_fd_list **fd_list);
int 	returnable(t_fd_list *fd_list, size_t *len_res);
int		put_fd_buf(char *buf, t_fd_list *fd_list, ssize_t len_buf);
int		put_result(char **res, t_fd_list *fd_list, size_t len_res);
void	*gnl_memmove(char *dst, char *src, size_t len);
char	*free_node(t_fd_list **fd_list);

#endif