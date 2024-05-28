/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_grammer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:39 by daeha             #+#    #+#             */
/*   Updated: 2024/05/28 17:14:18 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
// 		 			| 	redirect_list simple_command
// 			    	|	simple_command cmd_suffix
// cmd_suffix 		::= io_redirect
// 					|   WORD
// 					| 	cmd_suffix io_redirect
// 			    	| 	cmd_suffix WORD
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
