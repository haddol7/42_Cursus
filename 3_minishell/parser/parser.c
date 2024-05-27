/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:39 by daeha             #+#    #+#             */
/*   Updated: 2024/05/27 20:59:58 by daeha            ###   ########.fr       */
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

void	set_token_next(t_token **token)
{
	*token = (*token)->next;
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
		set_token_next(token);
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
		set_token_next(token);
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

// simple_command 	::= WORD
// 		 		| 	redirect_list simple_command
// 			    |	simple_command cmd_suffix
t_node	*simple_command(t_token **token)
{
	char	**arg;
	t_node	*cmd;
	t_node	*redir;
	
	if (is_token_redir(*token))
		redir = redirect_list(token);
	if (is_token(token, T_WORD))
		arg = new_cmd_arg((*token)->value);
	while (is_token_redir(*token) || is_token(*token, T_WORD))
	{
		if (is_token_redir(*token))
			new_child_node(redir, token, LEFT);
		else
			append_cmd_arg((*token)->value);
	}

	return (cmd);
}
