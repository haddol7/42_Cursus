/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:48:37 by daeha             #+#    #+#             */
/*   Updated: 2024/05/30 15:39:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node *parser(t_token **token)
{
	t_node	*ast;
	if (!is_token(*token, T_EOF))
	{
		ast = list(token);
		if (!(is_token(*token, T_EOF)))
		{
			return (syntax_error_test(*token, &ast));
			//setsignal_error
		}
	}
	else
		return (NULL);
	return (ast);
}

void	free_tree(t_node **node)
{
	char **head;
	
	if (node == NULL || (*node) == NULL)
		return ;
	free_tree(&(*node)->left);
	free_tree(&(*node)->right);
	if ((*node)->cmd != NULL)
	{	
		head = (*node)->cmd;
		while (*(*node)->cmd)
		{
			printf("%s\n",*(*node)->cmd);
			free(*(*node)->cmd);
			(*node)->cmd++;
		}
		free(head);
	}
	free(*node);
	*node = NULL;
}
