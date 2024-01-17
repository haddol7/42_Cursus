/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:48:19 by daeha             #+#    #+#             */
/*   Updated: 2024/01/17 22:46:51 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_node(t_fd_list **fd_list)
{
	t_fd_list	*temp;

	if (*fd_list == (*fd_list)->head)
	{
		if((*fd_list)->buffer != NULL)
			free((*fd_list)->buffer);
		(*fd_list)->buffer = NULL;
		(*fd_list)->head = NULL;
		(*fd_list)->fd = -1;
		(*fd_list)->len = 0;
		(*fd_list)->next = NULL;
		free(*fd_list);
		*fd_list = NULL;
		return (NULL);
	}
	temp = (*fd_list)->head;
	while (temp->next != *fd_list && temp->next != NULL)
		temp = temp->next;
	temp->next = (*fd_list)->next;
	if ((*fd_list)->buffer != NULL)
		free((*fd_list)->buffer);
	(*fd_list)->buffer = NULL;
	free((*fd_list));
	*fd_list = temp;
	(*fd_list)->next = temp->next;
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
