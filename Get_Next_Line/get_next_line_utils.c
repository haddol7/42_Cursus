/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:48:51 by daeha             #+#    #+#             */
/*   Updated: 2024/01/13 18:32:14 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_node(t_fd_list **fd_list)
{
	t_fd_list	*temp;

	temp = (*fd_list)->head;
	while (temp->next != (*fd_list) && temp->next != NULL)
		temp = temp->next;
	temp->next = (*fd_list)->next;
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
