/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:48:37 by daeha             #+#    #+#             */
/*   Updated: 2024/05/30 17:47:59 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//TODO : 시그널 처리
t_node	*parser(t_token **token)
{
	t_node	*ast;
	t_token	*head;

	ast = NULL;
	head = *token;
	if (!is_token(*token, T_EOF))
	{
		ast = list(token);
		if (head == *token || !is_token(*token, T_EOF))
		{
			return (syntax_error_test(*token, NULL));
		}
	}
	ms_free_all_token(&head);
	return (ast);
}

void	*free_tree(t_node **node)
{
	char	**head;

	if (node == NULL || (*node) == NULL)
		return (NULL);
	free_tree(&(*node)->left);
	free_tree(&(*node)->right);
	if ((*node)->cmd != NULL)
	{	
		head = (*node)->cmd;
		while (*(*node)->cmd)
		{
			free(*(*node)->cmd);
			(*node)->cmd++;
		}
		free(head);
	}
	free(*node);
	*node = NULL;
	return (NULL);
}
