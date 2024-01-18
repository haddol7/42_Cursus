/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:48:19 by daeha             #+#    #+#             */
/*   Updated: 2024/01/19 00:55:12 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
