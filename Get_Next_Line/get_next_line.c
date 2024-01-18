/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:23:46 by daeha             #+#    #+#             */
/*   Updated: 2024/01/18 18:10:13 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	char				*res;
	char				buf[BUFFER_SIZE];
	size_t				len_res;
	ssize_t				len_buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || !find_fd(fd, &fd_list))
		return (NULL);
	while (!returnable(fd_list, &len_res))
	{	
		len_buf = read(fd, buf, BUFFER_SIZE);
		if (len_buf < 0 || len_buf + fd_list->len == 0)
			return (free_node(&fd_list));
		if (!put_fd_buf(buf, fd_list, len_buf))
			return (free_node(&fd_list));
	}
	if (!put_result(&res, fd_list, len_res))
		return (free_node(&fd_list));
	return (res);
}

int	find_fd(int fd, t_fd_list **fd_list)
{	
	t_fd_list	*new_list;
	t_fd_list	*temp;

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
	temp = (*fd_list)->head;
	while (temp != NULL)
	{
		if (temp->fd == fd)
		{
			*fd_list = temp;
			return (1);
		}
		else if (temp->next == NULL)
			break;
		temp = temp->next;
	}
	new_list = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (new_list == NULL)
		return (0);
	new_list->fd = fd;
	new_list->buffer = NULL;
	new_list->len = 0;
	new_list->head = (*fd_list)->head;
	new_list->next = NULL;
	temp->next = new_list;
	*fd_list = new_list;
	return (1);
}

int returnable(t_fd_list *fd_list, size_t *len_res)
{
	size_t	i;

	i = 0;
	*len_res = 0;
	while (i < fd_list->len)
	{
		if (fd_list->buffer[i] == '\n' || fd_list->buffer[i] == '\0')
		{
			*len_res = i + 1;
			return (1);
		}
		i++;
	}
	return (0);	
}

int put_fd_buf(char *buf, t_fd_list *fd_list, ssize_t len_buf)
{
	char	*new_fd_buf;

	if (len_buf == 0)
	{
		if (fd_list->len > 0)
			buf[len_buf++] = '\0';
		else
			return (0);
	}
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

//TODO: add condition that fd_list->buffer has only \0
int put_result(char **res, t_fd_list *fd_list, size_t len_res)
{
	char	*new_fd_buf;
	size_t	len_new_res;

	len_new_res = len_res;
	if (fd_list->buffer[len_res - 1] == '\n')
		len_new_res++;
	*res = (char *)malloc(sizeof(char) * (len_new_res));
	if (*res == NULL)
		return (0);
	gnl_memmove(*res, fd_list->buffer, len_res);
	(*res)[len_new_res - 1] = '\0';
	fd_list->len -= len_res;
	if (fd_list->len == 0)
	{
		free(fd_list->buffer);
		fd_list->buffer = NULL;
		return (1);
	}
	new_fd_buf = (char *)malloc(sizeof(char) * fd_list->len);
	if (new_fd_buf == NULL)
	{
		free(*res);
		return (0);
	}
	gnl_memmove(new_fd_buf, fd_list->buffer + len_res, fd_list->len);
	free(fd_list->buffer);
	fd_list->buffer = new_fd_buf;
	return (1);
}
