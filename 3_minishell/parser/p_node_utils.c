/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_node_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:14:58 by daeha             #+#    #+#             */
/*   Updated: 2024/05/30 00:38:37 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//새로운 부모 노드를 만듭니다.
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

//새로운 cmd 노드를 만듭니다.
//주로 N_CMD 노드 혹은 
//입출력과 관련된 N_HEREDOC, N_INPUT, N_OUTPUT, N_APPEND를 생성할 때 사용합니다.
t_node *new_cmd_node(t_node_type type, char **arg)
{
	t_node	*node;

	ft_putendl_fd("utils : new_cmd_node", 2);
	node = (t_node *)malloc(sizeof(t_node));

	//if (node == NULL)
		//error here
	node->type = type;
	node->cmd = arg;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

//추가하고 싶은 노드를 redir 노드 최하단 왼쪽 자식으로 붙입니다.
//붙여지는 node는 N_CMD이거나 N_SHELL입니다.
//
//NOTE : 모든 redir->right에는 redirection할 filename이 cmd[0]에 char * 형태로 있습니다.
t_node *link_redir_to_node(t_node *node, t_node *redir)
{
	t_node	*head;
	t_node	*cur;
	
	if (redir == NULL)
		return (NULL);
	head = redir;
	cur = redir;
	while(cur && cur->left)
		cur = cur->left;
	cur->left = node;
	return (head);
}

// 기존에 있던 redir tree의 최하단 왼쪽 leaf에 새롭게 추가된 io node를 넣습니다.
// NOTE : redir에 NULL이 들어올 수 있습니다.
//		-> 하나의 redir 노드를 만들어 return 합니다.
t_node	*append_redir_node(t_node *redir, t_token **token)
{
	t_node	*new_io;
	t_node	*head;
	t_node	*cur;

	ft_putendl_fd("utils : append_redir_node", 2);
	head = redir;
	cur = redir;
	new_io = io_redirect(token);
	if (redir != NULL)
	{
		while (cur && cur->left)
			cur = cur->left;
		cur->left = new_io;	
	}
	else
		head = new_io;
	return (head);
}

//기존에 있던 2차원 배열의 arg 맨 뒤에 있는 값을, 
//현재 token->value에 해당하는 값을 추가로 넣습니다.
char **append_cmd_arg(char **arg, t_token **token)
{
	char 	**new_arg;
	size_t	size;
	size_t	i;

	ft_putendl_fd("utils : append_cmd_arg", 2);
	size = 2;
	while (arg && arg[size - 2])
		size++;
	new_arg = (char **)malloc(sizeof(char *) * (size));
	// if (new_arg)
	// 	//mem_error
	i = 1;
	while (++i < size)
	{
		new_arg[i - 2] = ft_strdup(arg[i - 2]);
		free(arg[i - 2]);
	}
	free(arg);
	new_arg[size - 2] = ft_strdup((*token)->value);
	new_arg[size - 1] = NULL;
	token_next(token);
	return (new_arg);
}
