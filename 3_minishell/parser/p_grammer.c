/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_grammer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:39 by daeha             #+#    #+#             */
/*   Updated: 2024/05/29 23:43:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//TODO : T_EOF 제대로 발생하는지 확인
//TODO : Syntax error 처리에 관한 방법 모색


//list ::= pipeline 
//     | list '&&' pipeline
//     | list '||' pipeline

//1. 조건연산자 뒤에 아무것도 없을 때
t_node	*list(t_token **token)
{
	t_node		*list;
	t_node_type	type;

	ft_putendl_fd("BNF : list", 2);
	
	list = pipeline(token);
	while (is_token(*token, T_AND_IF) || is_token(*token, T_OR_IF))
	{
		if (is_token(*token, T_AND_IF))
			type = N_AND;
		else
			type = N_OR;
		list = new_parent_node(type, list, NULL);
		token_next(token);
		list->right = pipeline(token);
		if (list->right == NULL)
			syntax_error_test(">> || OR &&");
	}
	return (list);
}

// pipeline ::= command
// 			| 	pipeline '|' command

//1. 파이프 뒤에 아무것도 없을 때
t_node *pipeline(t_token **token)
{
	t_node	*pipe;

	ft_putendl_fd("BNF : pipe", 2);

	pipe = command(token);
	while (is_token(*token, T_PIPE))
	{
		pipe = new_parent_node(N_PIPE, pipe, NULL);
		token_next(token);
		pipe->right = command(token);
		if (pipe->right == NULL)
			syntax_error_test(">> |");
	}
	return (pipe);
}

// command	::= simple_command
// 			| 	subshell

// 1. subshell에서 문법 오류를 발생시켰을 때
// 2. simple cmd의 문법 오류
t_node *command(t_token **token)
{
	ft_putendl_fd("BNF : cmd", 2);

	if (is_token(*token, T_LPAREN))
		return (subshell(token));
	else if (is_token(*token, T_WORD) || is_token_redir(*token))
		return (simple_command(token));
	return (NULL);
}

//subshell 	::= '(' list ')' redirect_list

// 1. 괄호가 제대로 닫히지 않았을 때
// 2. redir이 제대로 반환되지 않았을 때??
t_node	*subshell(t_token **token)
{
	t_node	*subshell;
	t_node	*node;
	t_node	*redir;
	
	ft_putendl_fd("BNF : subshell", 2);

	token_next(token);
	node = list(token);
	if (!is_token(*token, T_RPAREN))
		syntax_error_test(">> )");
	token_next(token);
	if (is_token_redir(*token))
	{
		redir = redirect_list(token);
		node = link_redir_to_node(node, redir);
	}
	subshell = new_parent_node(N_SUBSHELL, node, NULL);
	return (subshell);
}

// simple_command 	::= WORD
// 		 			| 	redirect_list simple_command
// 			    	|	simple_command cmd_suffix
// cmd_suffix 		::= io_redirect
// 					|   WORD
// 					| 	cmd_suffix io_redirect
// 			    	| 	cmd_suffix WORD

//1. < 뒤에 WORD가 아닐 때
t_node	*simple_command(t_token **token)
{
	char	**arg;
	t_node	*cmd;
	t_node	*redir;
	
	arg = NULL;
	redir = NULL;
	ft_putendl_fd("BNF : simp cmd", 2);
	if (is_token_redir(*token))
		redir = redirect_list(token);
	while (is_token(*token, T_WORD) || is_token_redir(*token))
	{
		if (is_token(*token, T_WORD))
			arg = append_cmd_arg(arg, token);
		else
			redir = append_redir_node(redir, token);
	}
	cmd = new_cmd_node(N_CMD, arg);
	if (redir != NULL)
		cmd = link_redir_to_node(cmd, redir);
	return (cmd);
}
