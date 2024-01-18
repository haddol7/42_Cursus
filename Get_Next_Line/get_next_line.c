/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:23:46 by daeha             #+#    #+#             */
/*   Updated: 2024/01/19 02:04:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_fd_list	*head;
	t_fd_list			*current;
	t_result			result;
	char				buf[BUFFER_SIZE];
	ssize_t				len_buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || !find_fd(fd, &head, &current))
		return (NULL);
	while (!returnable(current, &(result.len)))
	{	
		len_buf = read(fd, buf, BUFFER_SIZE);
		if (len_buf < 0 || len_buf + current->len == 0)
			return (free_node(&head, &current));
		if (!put_fd_buf(buf, current, len_buf))
			return (free_node(&head, &current));
	}
	if (!put_result(&result, &head, &current))
		return (free_node(&head, &current));
	return (result.str);
}

int	find_fd(int fd, t_fd_list **head, t_fd_list **cur)
{	
	t_fd_list	*new_list;

	if (*head == NULL)
		return (init_gnl(fd, head, cur));
	*cur = *head;
	while (*cur != NULL)
	{
		if ((*cur)->fd == fd)
			return (1);
		else if ((*cur)->rear == NULL)
			break ;
		(*cur) = (*cur)->rear;
	}
	new_list = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (new_list == NULL)
		return (0);
	new_list->fd = fd;
	new_list->buffer = NULL;
	new_list->len = 0;
	new_list->front = *cur;
	new_list->rear = NULL;
	(*cur)->rear = new_list;
	*cur = (*cur)->rear;
	return (1);
}

int	returnable(t_fd_list *cur, size_t *len_res)
{
	size_t	i;

	i = 0;
	*len_res = 0;
	while (i < cur->len)
	{
		if (cur->buffer[i] == '\n' || cur->buffer[i] == '\0')
		{
			*len_res = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	put_fd_buf(char *buf, t_fd_list *cur, ssize_t len_buf)
{
	char	*new_fd_buf;

	if (len_buf == 0)
	{
		if (cur->len > 0)
			buf[len_buf++] = '\0';
		else
			return (0);
	}
	new_fd_buf = (char *)malloc(sizeof(char) * (cur->len + len_buf));
	if (new_fd_buf == NULL)
		return (0);
	gnl_memmove(new_fd_buf, cur->buffer, cur->len);
	gnl_memmove(new_fd_buf + cur->len, buf, len_buf);
	if (cur->buffer != NULL)
		free(cur->buffer);
	cur->buffer = new_fd_buf;
	cur->len += len_buf;
	return (1);
}

int	put_result(t_result *res, t_fd_list **head, t_fd_list **cur)
{
	size_t	len_new_res;

	len_new_res = res->len;
	if ((*cur)->buffer[res->len - 1] == '\n')
		len_new_res++;
	res->str = (char *)malloc(sizeof(char) * (len_new_res));
	if (res->str == NULL)
		return (0);
	gnl_memmove(res->str, (*cur)->buffer, res->len);
	(res->str)[len_new_res - 1] = '\0';
	(*cur)->len -= res->len;
	if (res->len == len_new_res)
	{
		(free_node(head, cur));
		return (1);
	}
	return (put_left_fd_buf(res, cur));
}
