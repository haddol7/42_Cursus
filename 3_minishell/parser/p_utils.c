/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:14:58 by daeha             #+#    #+#             */
/*   Updated: 2024/06/18 00:19:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*new_parent_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = ft_malloc(sizeof(t_node));
	node->cmd = NULL;
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*new_cmd_node(t_node_type type, char **arg)
{
	t_node	*node;

	node = (t_node *)ft_malloc(sizeof(t_node));
	node->type = type;
	node->cmd = arg;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*link_redir_to_node(t_node *node, t_node *redir)
{
	t_node	*head;
	t_node	*cur;

	if (redir == NULL)
		return (node);
	head = redir;
	cur = redir;
	while (cur && cur->left)
		cur = cur->left;
	cur->left = node;
	return (head);
}

t_node	*append_redir_node(t_node *redir, t_token **token)
{
	t_node	*new_io;
	t_node	*head;
	t_node	*cur;

	head = redir;
	cur = redir;
	new_io = io_redirect(token);
	if (new_io == NULL)
		return (NULL);
	if (redir)
	{
		while (cur && cur->left)
			cur = cur->left;
		cur->left = new_io;
	}
	else
		head = new_io;
	return (head);
}

char	**append_cmd_arg(char **arg, t_token **token)
{
	char	**new_arg;
	size_t	size;
	size_t	i;

	size = 2;
	while (arg && arg[size - 2])
		size++;
	new_arg = (char **)ft_malloc(sizeof(char *) * (size));
	i = 1;
	while (++i < size)
		new_arg[i - 2] = arg[i - 2];
	if (arg != NULL)
		free(arg);
	new_arg[size - 2] = ft_strdup((*token)->value);
	new_arg[size - 1] = NULL;
	token_next(token);
	return (new_arg);
}
