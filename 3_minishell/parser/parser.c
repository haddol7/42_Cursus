/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:48:37 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 23:15:14 by daeha            ###   ########.fr       */
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
		syntax_error(token);
	return (ast);
}

void	*free_all_tree(t_node **node)
{
	if (node == NULL || *node == NULL)
		return (NULL);
	free_all_tree(&(*node)->left);
	free_all_tree(&(*node)->right);
	if ((*node)->cmd != NULL)
		free_arg(&(*node)->cmd);
	free(*node);
	*node = NULL;
	return (NULL);
}

void	*free_arg(char ***cmd)
{
	char	**head;
	size_t	i;
	
	i = 0;
	head = *cmd;
	while (head[i])
	{
		if (head[i] != NULL)
			free(head[i]);
		head[i] = NULL;
		i++;
	}
	free(head);
	head = NULL;
	return (NULL);
}
