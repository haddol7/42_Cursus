/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_grammer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:47:24 by daeha             #+#    #+#             */
/*   Updated: 2024/05/28 16:47:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
// io_file 		::= '<' WORD
// 			    | 	'>' WORD
// 				| 	'>>' WORD
// io_here 	    ::= '<<' WORD
t_node	*io_redirect(t_token **token)
{
	char 		**arg;
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
	arg = (char **)malloc(sizeof(char *) * 2);
	if (arg == NULL)
		//mallocerror
	arg[0] = ft_strdup((*token)->value);
	arg[1] = NULL;
	io = new_cmd_node(node_type, arg);
	token_next(token);
	return (io);
}
