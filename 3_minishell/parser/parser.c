/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:48:37 by daeha             #+#    #+#             */
/*   Updated: 2024/06/09 16:50:46 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parser(t_token *token)
{
	t_node	*ast;
	t_token	*head;

	ast = NULL;
	head = token;
	if (head == NULL)
		return (NULL);
	ast = list(&token);
	if (head == token || !is_token(token, T_EOF))
		syntax_error(token, &ast);
	return (ast);
}

void	*free_tree(t_node **node)
{
	if (node == NULL || *node == NULL)
		return (NULL);
	free_tree(&(*node)->left);
	free_tree(&(*node)->right);
	if ((*node)->cmd != NULL)
		free_arg(&(*node)->cmd);
	free(*node);
	*node = NULL;
	return (NULL);
}

void	*free_arg(char ***cmd)
{
	char	**head;
	char	**cur;

	if (*cmd != NULL)
	{
		head = *cmd;
		cur = *cmd;
		while (*cur)
		{
			free(*cur);
			*cur = NULL;
			cur++;
		}
		free(head);
		head = NULL;
	}
	return (NULL);
}
