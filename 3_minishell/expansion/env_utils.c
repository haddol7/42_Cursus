/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:43:00 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/17 23:39:49 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_env	*env_new(char *name, char *content)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		handle_error("exit : malloc error6", 1, 0);
	node->key = name;
	node->value = content;
	if (name != NULL && content != NULL)
		node->complete = 1;
	else
		node->complete = 0;
	node->next = NULL;
	return (node);
}

t_env	*env_last(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	if (head == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	env_add_back(t_env **head, t_env *new)
{
	t_env	*last;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = env_last(*head);
		last->next = new;
	}
}

int	env_free_all(t_env **head)
{
	t_env	*to_free;
	t_env	*tmp;

	to_free = *head;
	while (to_free != NULL)
	{
		tmp = to_free->next;
		if (to_free->key != NULL)
		{
			free(to_free->key);
			to_free->key = NULL;
		}
		if (to_free->value != NULL)
		{
			free(to_free->value);
			to_free->value = NULL;
		}
		free(to_free);
		to_free = tmp;
	}
	*head = NULL;
	return (0);
}
