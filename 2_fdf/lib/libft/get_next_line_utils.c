/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:48:51 by daeha             #+#    #+#             */
/*   Updated: 2024/03/07 17:36:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	init_gnl(int fd, t_fd_list **head, t_fd_list **cur)
{	
	*head = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (*head == NULL)
		return (0);
	(*head)->fd = fd;
	(*head)->buffer = NULL;
	(*head)->len = 0;
	(*head)->front = NULL;
	(*head)->rear = NULL;
	*cur = *head;
	return (1);
}

char	*free_node(t_fd_list **head, t_fd_list **cur)
{
	if ((*cur)->front != NULL)
		((*cur)->front)->rear = (*cur)->rear;
	if ((*cur)->rear != NULL)
		((*cur)->rear)->front = (*cur)->front;
	if ((*cur)->buffer != NULL)
		free((*cur)->buffer);
	(*cur)->buffer = NULL;
	(*cur)->fd = -1;
	(*cur)->len = 0;
	if ((*cur)->front == NULL)
		*head = (*cur)->rear;
	free(*cur);
	(*cur) = NULL;
	return (NULL);
}

void	*gnl_memmove(char *dst, char *src, size_t len)
{
	size_t	i;

	if (src < dst && len != 0)
	{
		i = len;
		while (i-- != 0)
			dst[i] = src[i];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	}
	return (dst);
}

int	put_left_fd_buf(t_result *res, t_fd_list **cur)
{
	char	*new_fd_buf;

	new_fd_buf = NULL;
	if ((*cur)->len != 0)
	{
		new_fd_buf = (char *)malloc(sizeof(char) * (*cur)->len);
		if (new_fd_buf == NULL)
		{
			free(res->str);
			return (0);
		}
		gnl_memmove(new_fd_buf, (*cur)->buffer + res->len, (*cur)->len);
	}
	free((*cur)->buffer);
	(*cur)->buffer = new_fd_buf;
	return (1);
}
