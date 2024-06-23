/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_grammer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:40:17 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 23:21:53 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

//list ::= pipeline 
//     | list '&&' pipeline
//     | list '||' pipeline
t_node	*list(t_token **token)
{
	t_node		*list;
	t_node_type	type;

	list = pipeline(token);
	while (list && (is_token(*token, T_AND_IF) || is_token(*token, T_OR_IF)))
	{
		if (is_token(*token, T_AND_IF))
			type = N_AND;
		else
			type = N_OR;
		list = new_parent_node(type, list, NULL);
		token_next(token);
		list->right = pipeline(token);
		if (list->right == NULL)
		{
			free_all_tree(&list);
			return (syntax_error(*token));
		}
	}
	return (list);
}

// pipeline ::= command
// 			| 	pipeline '|' command
t_node	*pipeline(t_token **token)
{
	t_node	*pipe;

	pipe = command(token);
	while (pipe && is_token(*token, T_PIPE))
	{
		pipe = new_parent_node(N_PIPE, pipe, NULL);
		token_next(token);
		pipe->right = command(token);
		if (pipe->right == NULL)
		{
			free_all_tree(&pipe);
			return (syntax_error(*token));
		}
	}
	return (pipe);
}

// command	::= simple_command
// 			| 	subshell
t_node	*command(t_token **token)
{	
	if (is_token(*token, T_LPAREN))
		return (subshell(token));
	else if (is_token(*token, T_WORD) || is_token_redir(*token))
		return (simple_command(token));
	return (NULL);
}

//subshell 	::= '(' list ')' redirect_list
t_node	*subshell(t_token **token)
{
	t_node	*subshell;
	t_node	*node;
	t_node	*redir;

	token_next(token);
	node = list(token);
	if (!is_token((*token), T_RPAREN) || !node)
	{
		free_all_tree(&node);
		return (syntax_error(*token));
	}
	subshell = new_parent_node(N_SUBSHELL, node, NULL);
	token_next(token);
	if (is_token_redir(*token))
	{
		redir = redirect_list(token);
		if (redir == NULL)
			return (free_all_tree(&subshell));
		subshell = link_redir_to_node(subshell, redir);
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
	t_node	*temp;

	arg = NULL;
	cmd = NULL;
	redir = NULL;
	while (is_token(*token, T_WORD) || is_token_redir(*token))
	{
		if (is_token(*token, T_WORD))
			arg = append_cmd_arg(arg, token);
		else
		{
			temp = append_redir_node(redir, token);
			if (temp == NULL)
				return (free_simple_command(arg, redir));
			else
				redir = temp;
		}
	}
	if (arg != NULL)
		cmd = new_cmd_node(N_CMD, arg);
	cmd = link_redir_to_node(cmd, redir);
	return (cmd);
}
