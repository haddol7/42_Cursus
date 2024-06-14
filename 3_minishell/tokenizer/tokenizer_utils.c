/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:53:29 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/14 22:34:58 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	handle_error(char *str, int code, t_token **head)
{
	write(2, str, ft_strlen(str));
	if (code == 1)
		exit(1);
	else
	{
		free_all_token(head);
		return (0);
	}
}

t_token	*ms_lstnew(char *value, t_token_type type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		handle_error("exit : malloc error9", 1, 0);
	node->type = type;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_token	*ms_lstlast(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (head == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ms_lstadd_back(t_token **head, t_token *new)
{
	t_token	*last;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = ms_lstlast(*head);
		last->next = new;
	}
}

int	free_all_token(t_token **head)
{
	t_token	*to_free;
	t_token	*tmp;

	to_free = *head;
	while (to_free != NULL)
	{
		tmp = to_free->next;
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
