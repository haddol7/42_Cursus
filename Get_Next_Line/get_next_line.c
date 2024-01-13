/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:23:46 by daeha             #+#    #+#             */
/*   Updated: 2024/01/13 18:33:08 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	char				*res;
	char				buf[BUFFER_SIZE + 1];
	size_t				len_res;
	ssize_t				len_buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || !find_fd(fd, &fd_list))
		return (NULL);

//	printf("%d %zu  %p %p %p %p\n", fd_list->fd, fd_list->len, fd_list->buffer, fd_list->next, fd_list, fd_list->head);
	
	while (!returnable(fd_list, &len_res))
	{	
		len_buf = read(fd, buf, BUFFER_SIZE);
		if (len_buf < 0)
			return (free_node(&fd_list));
		if (!put_fd_buf(buf, fd_list, len_buf))
			return (free_node(&fd_list));
	}
	if (!put_result(&res, fd_list, len_res))
		return (free_node(&fd_list));

//	printf("%d %zu  %p %p %p %p\n", fd_list->fd, fd_list->len, fd_list->buffer, fd_list->next, fd_list, fd_list->head);
	return (res);
}

int	find_fd(int fd, t_fd_list **fd_list)
{	
	if (*fd_list == NULL)
	{
		*fd_list = (t_fd_list *)malloc(sizeof(t_fd_list));
		if (*fd_list == NULL)
			return (0);
		(*fd_list)->fd = fd;
		(*fd_list)->buffer = NULL;
		(*fd_list)->len = 0;
		(*fd_list)->head = *fd_list;
		(*fd_list)->next = NULL;
		return (1);
	}
	*fd_list = (*fd_list)->head; 
	while (*fd_list != NULL && (*fd_list)->fd != fd)
		*fd_list = (*fd_list)->next;
	if  (*fd_list == NULL)
	{
		*fd_list = (t_fd_list *)malloc(sizeof(t_fd_list));
		if (*fd_list == NULL)
			return (0);
		(*fd_list)->fd = fd;
		(*fd_list)->buffer = NULL;
		(*fd_list)->len = 0;
		(*fd_list)->next = NULL;
	}
	return (1);
}

int returnable(t_fd_list *fd_list, size_t *len_res)
{
	size_t	i;

	i = 0;
	while (i < fd_list->len)
	{
		if (fd_list->buffer[i] == '\n' || fd_list->buffer[i] == '\0')
		{
			*len_res = i + 1;
			return (1);
		}
		i++;
	}
	*len_res = 0;
	return (0);	
}

int	put_fd_buf(char *buf, t_fd_list *fd_list, ssize_t len_buf)
{
	char	*new_fd_buf;

	if (len_buf <= BUFFER_SIZE && buf[len_buf] != '\n')
		buf[len_buf] = '\0';
	if (fd_list->len + len_buf == 0)
		return (0);
	new_fd_buf = (char *)malloc(sizeof(char) * (fd_list->len + len_buf));
	if (new_fd_buf == NULL)
		return (0);
	gnl_memmove(new_fd_buf, fd_list->buffer, fd_list->len);
	gnl_memmove(new_fd_buf + fd_list->len, buf, len_buf);
	if (fd_list->buffer != NULL)
		free(fd_list->buffer);	
	fd_list->buffer = new_fd_buf;
	fd_list->len += len_buf;
	return (1);
}

int	put_result(char **res, t_fd_list *fd_list, size_t len_res)
{
	char	*new_fd_buf;
	char	*new_res;

	new_res = (char *)malloc(sizeof(char) * len_res);
	if (new_res == NULL)
		return (0);
	gnl_memmove(new_res, fd_list->buffer, len_res);
	*res = new_res;
	if (fd_list->buffer[fd_list->len - 1] == '\0')
	{
		free_node(&fd_list);
		return (1);
	}
	fd_list->len -= len_res;
	if (fd_list->len == 0)
	{
		free(fd_list->buffer);
		fd_list->buffer = NULL;
	}
	new_fd_buf = (char *)malloc(sizeof(char) * (fd_list->len));
	if (new_fd_buf == NULL)
	{
		free(new_res);
		return (0);
	}
	gnl_memmove(new_fd_buf, fd_list->buffer + len_res, fd_list->len);
	free(fd_list->buffer);
	fd_list->buffer = new_fd_buf;
	return (1);
}
