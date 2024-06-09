/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:44:24 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/08 13:16:06 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_new_cmd	*cmd_new(char *cmd)
{
	t_new_cmd	*node;

	node = (t_new_cmd *)malloc(sizeof(t_new_cmd));
	if (node == NULL)
		handle_error("exit : malloc error7", 1, 0);
	node->cmd = cmd;
	node->next = NULL;
	return (node);
}

t_new_cmd	*cmd_last(t_new_cmd *head)
{
	t_new_cmd	*tmp;

	tmp = head;
	if (head == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	cmd_add_back(t_new_cmd **head, char *new)
{
	t_new_cmd	*last;
	t_new_cmd	*new_node;

	new_node = cmd_new(new);
	if (head == NULL)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		last = cmd_last(*head);
		last->next = new_node;
	}
}

int	list_free_all(t_new_cmd **head)
{
	t_new_cmd	*to_free;
	t_new_cmd	*tmp;

	to_free = *head;
	while (to_free != NULL)
	{
		tmp = to_free->next;
		if (to_free != NULL)
			free(to_free->cmd);
		free(to_free);
		to_free = tmp;
	}
	*head = NULL;
	return (0);
}

int	get_cmd_node_num(t_new_cmd *head)
{
	t_new_cmd	*node;
	int			cnt;

	node = head;
	cnt = 0;
	while (node != NULL)
	{
		node = node->next;
		cnt++;
	}
	return (cnt);
}

void	print_all_cmd(t_new_cmd *head)
{
	t_new_cmd	*tmp;

	tmp = head;
	printf("------------cmd-------------");
	while (tmp != NULL)
	{
		printf("|%s|\n", tmp->cmd);
		tmp = tmp->next;
	}
	printf("----------------------------");
}