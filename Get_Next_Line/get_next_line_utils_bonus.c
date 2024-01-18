/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:48:19 by daeha             #+#    #+#             */
/*   Updated: 2024/01/18 23:26:12 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
char	*free_node(t_fd_list **cur)
{
	t_fd_list	*temp;

	temp = *cur;
	if (temp->front != NULL)
		temp->front->rear = temp->rear;
	if (temp->rear != NULL)
		temp->rear->front = temp->front;
	if (temp->buffer != NULL)
		free(temp->buffer);
	temp->buffer = NULL;
	temp->fd = -1;
	temp->len = 0;
	free(temp);
	temp = temp->rear;
	*cur = NULL;
	return (NULL);
}
*/

char	*free_node(t_fd_list **cur)
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
	free(*cur);
	(*cur) = (*cur)->rear;
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
