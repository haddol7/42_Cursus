/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:48:51 by daeha             #+#    #+#             */
/*   Updated: 2024/01/18 17:58:13 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_node(t_fd_list **fd_list)
{
	t_fd_list	*front;

	if (*fd_list == (*fd_list)->head)
	{
		if((*fd_list)->buffer != NULL)
			free((*fd_list)->buffer);
		(*fd_list)->buffer = NULL;
		free(*fd_list);
		*fd_list = NULL;
		return (NULL);
	}
	front = (*fd_list)->head;
	while (front->next != *fd_list)
		front = front->next;
	if ((*fd_list)->buffer != NULL)
		free((*fd_list)->buffer);
	(*fd_list)->buffer = NULL;
	front->next = (*fd_list)->next;
	free(*fd_list);
	*fd_list = front;
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
