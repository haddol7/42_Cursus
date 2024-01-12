/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:15:44 by daeha             #+#    #+#             */
/*   Updated: 2024/01/12 20:58:53 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 42

typedef struct	s_fd_list
{
	int					fd;
	char				*buffer;
	size_t				len;
	struct s_fd_list	*next;
} t_fd_list;

char	*get_next_line(int fd);
char	*free_node(t_fd_list *fd_list);
int	find_fd(int fd, t_fd_list **file);
int	put_result(t_fd_list *file, char **res, char *buf, size_t offset);
int	put_left_buf(t_fd_list *file, char *buf, ssize_t read_bytes, size_t offset);
size_t	is_in_newline_or_eof(char *buffer, ssize_t read_bytes, size_t *offset);
size_t	gnl_strlen(char *buffer);
void	*gnl_memmove(char *dst, char *src, size_t len);




#endif
