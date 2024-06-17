/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:16:49 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/17 19:18:10 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_one_cmd(t_new_cmd **head, t_new_cmd **node)
{
	t_new_cmd	*tmp;

	tmp = *head;
	if (tmp == NULL || (*node) == NULL)
		return ;
	if (*head == *node)
	{
		*head = (*node)->next;
		free((*node)->cmd);
		free((*node));
		*node = NULL;
	}
	else
	{
		while (tmp->next != (*node))
			tmp = tmp->next;
		tmp->next = (*node)->next;
		free((*node)->cmd);
		free(*node);
		*node = NULL;
	}
}

t_new_cmd	*join_sub_cmd(t_new_cmd **head, t_new_cmd *node, \
							t_new_cmd *sub_list)
{
	t_new_cmd	*next;
	t_new_cmd	*sub_end;

	if (node == NULL)
	{
		*head = sub_list;
		return (NULL);
	}
	next = node->next;
	node->next = sub_list;
	sub_end = cmd_last(sub_list);
	if (sub_end != NULL)
		sub_end->next = next;
	return (next);
}
