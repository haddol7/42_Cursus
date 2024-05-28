/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_node_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:14:58 by daeha             #+#    #+#             */
/*   Updated: 2024/05/28 20:59:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*new_parent_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		//error here
	node->cmd = NULL;
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}

t_node *new_cmd_node(t_node_type type, char **arg)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		//error here
	node->type = type;
	node->cmd = arg;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

//redir 노드의 최하단 leaf의 left에 node 포인터를 넣는 함수
t_node *link_redir_to_node(t_node *node, t_node **redir)
{
	t_node	*head;
	
	head = *redir;
	if (*redir == NULL)
		//error?
	while(*redir && (*redir)->left)
		*redir = (*redir)->left;
	(*redir)->left = node;
	return (head);
}

void	append_redir_node(t_node *redir, t_token **token)
{
	t_node	*new_io;

	new_io = io_redirect(token);
	if (redir == NULL)
		// error ?
	while (redir && redir->left)
		redir = redir->left;
	redir->left = new_io;
}

char **append_cmd_arg(char **arg, t_token **token)
{
	char 	**new_arg;
	size_t	size;
	size_t	i;

	size = 0;
	while (arg + size)
		size++;
	new_arg = (char **)malloc(sizeof(char *) * (size + 2));
	if (new_arg)
		//mem_error
	i = 1;
	while (++i < size)
	{
		new_arg[i - 2] = ft_strdup(arg[i - 2]);
		free(arg[i - 2]);
	}
	free(arg);
	new_arg[size] = ft_strdup((*token)->value);
	new_arg[size + 1] = NULL;
	token_next(token);

	printf("%s\n", (*token)->value);

	return (new_arg);
}
