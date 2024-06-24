/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:48:37 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 04:35:09 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

t_node	*parser(t_token *token)
{
	t_bool	error;
	t_node	*ast;
	t_token	*head;

	ast = NULL;
	head = token;
	if (head == NULL)
		return (NULL);
	set_parser_error(FALSE);
	ast = list(&token);
	if (head == token || !is_token(token, T_EOF))
		syntax_error(token);
	error = *get_parser_error();
	if (error)
		free_all_tree(&ast);
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

t_bool	*get_parser_error(void)
{
	static t_bool	s_syntax_error;

	return (&s_syntax_error);
}

void	set_parser_error(t_bool is_error)
{
	t_bool	*status;

	status = get_parser_error();
	*status = is_error;
}
