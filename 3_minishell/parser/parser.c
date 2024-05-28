/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:39 by daeha             #+#    #+#             */
/*   Updated: 2024/05/28 15:39:50 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define LEFT 0
#define RIGHT 1

t_bool	is_token_redir(t_token *token)
{
	if (is_token(token, T_DLESS) || is_token(token, T_DGREAT) || \
		is_token(token, T_LESS) || is_token(token, T_GREAT))
		return (TRUE);
	return (FALSE);
}

t_bool	is_token(t_token *token, t_token_type type)
{
	if (token == NULL)
	{
		ft_putendl_fd("token is NULL!", 2);
		return (FALSE);
	}
	if (token->type == type)
		return (TRUE);
	else
		return (FALSE);
}

void	token_next(t_token **token)
{
	if ((*token)->type == T_EOF)
		return ;
	if ((*token) == NULL)
		ft_putendl_fd("이런 일은 있을 수 없다고!!!! 👺🤯🤬", stderr);
	*token = (*token)->next;
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

//redir 노드의 최하단 leaf의 left에 node 포인터를 넣는 함수
t_node *link_redir_to_node(t_node *node, t_node **redir)
{
	t_node	*head;
	
	head = *redir;
	if (redir == NULL)
		//error?
	while(*redir && (*redir)->left)
		(*redir)->left;
	(*redir)->left = node;
	return (head);
}

//list ::= pipeline 
//     | list '&&' pipeline
//     | list '||' pipeline
t_node	*list(t_token **token)
{
	t_node		*ast;
	t_node_type	type;

	ast = pipeline(token);
	while (is_token(token, T_AND_IF) || is_token(token, T_OR_IF))
	{
		if (is_token(token, T_AND_IF))
			type = N_AND;
		else
			type = N_OR;
		ast = new_parent_node(type, ast, NULL);
		token_next(token);
		ast->right = pipeline(token);
			//syntax error here
	}
	return (ast);
}

// pipeline ::= command
// 			| 	pipeline '|' command
t_node *pipeline(t_token **token)
{
	t_node	*pipe;

	pipe = command(token);
	while (is_token(*token, T_PIPE))
	{
		pipe = new_parent_node(T_PIPE, pipe, NULL);
		token_next(token);
		pipe->right = command(token);
	}
	return (pipe);
}

// command	::= simple_command
// 			| 	subshell
t_node *command(t_token **token)
{
	t_node	*cmd;

	if (is_token(*token, T_LPAREN))
		cmd = subshell(token);
	else
		cmd = simple_command(token);
	return (cmd);
}

//subshell 	::= '(' list ')' redirect_list
t_node	*subshell(t_token **token)
{
	t_node	*subshell;
	t_node	*node;
	t_node	*redir;
	
	token_next(token);
	node = list(token);
	if (!is_token(*token, T_RPAREN))
		//syntax errror
	token_next(token);
	if (is_token_redir(*token))
	{
		redir = redirect_list(token);
		subshell = link_redir_to_node(subshell, &redir);
	}
	return (subshell);
}

// simple_command 	::= WORD
// 		 		| 	redirect_list simple_command
// 			    |	simple_command cmd_suffix
t_node	*simple_command(t_token **token)
{
	char	**arg;
	t_node	*cmd;
	t_node	*redir;
	
	arg = NULL;
	if (is_token_redir(*token))
		redir = redirect_list(token);
	while (is_token(*token, T_WORD) || is_token_redir(*token))
	{
		if (is_token_redir(*token))
			append_redir_node(redir, token);
		else
			arg = append_cmd_arg(arg, token);
	}
	cmd = new_cmd_node(N_CMD, arg);
	cmd = link_redir_to_node(cmd, &redir);
	return (cmd);
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
		new_arg[i - 2] = arg[i - 2];
		free(arg[i - 2]);
	}
	free(arg);
	new_arg[size - 2] = ft_strdup((*token)->value);
	new_arg[size - 1] = NULL;
	token_next(token);
	return (new_arg);
}

//redirect_list ::= io_redirect
//					redirect_list io_redirect
t_node *redirect_list(t_token **token)
{
	t_node	*redir;

	redir = io_redirect(token);
	while (is_token_redir(*token))
		append_redir_node(redir, *token);
	return (redir);
}

// io_redirect	::= io_file
// 				| 	io_here
t_node	*io_redirect(t_token **token)
{
	t_node		*io;
	t_node_type	node_type;

	if ((*token)->type == T_GREAT)
		node_type = N_INPUT;
	else if ((*token)->type == T_LESS)
		node_type = N_OUTPUT;
	else if ((*token)->type == T_DLESS)
		node_type = N_APPEND;
	else
		node_type = N_HERE_DOC;
	token_next(token);
	if (!is_token(*token, T_WORD))
		//syntax_error
	io = new_cmd_node(node_type, (*token)->value);
	token_next(token);
	return (io);
}
