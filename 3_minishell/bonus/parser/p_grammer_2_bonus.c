/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_grammer_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:47:24 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

//redirect_list ::= io_redirect
//					redirect_list io_redirect
t_node	*redirect_list(t_token **token)
{
	t_node	*redir;
	t_node	*head;

	redir = io_redirect(token);
	while (redir && is_token_redir(*token))
	{
		head = redir;
		if (!append_redir_node(redir, token))
			return (free_all_tree(&head));
	}
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
	t_node		*io;
	t_node_type	node_type;
	char		**arg;

	if ((*token)->type == T_GREAT)
		node_type = N_OUTPUT;
	else if ((*token)->type == T_LESS)
		node_type = N_INPUT;
	else if ((*token)->type == T_DLESS)
		node_type = N_HERE_DOC;
	else
		node_type = N_APPEND;
	token_next(token);
	if (!is_token(*token, T_WORD))
		return (syntax_error(*token));
	arg = (char **)ft_malloc(sizeof(char *) * 2);
	arg[0] = ft_strdup((*token)->value);
	arg[1] = NULL;
	io = new_cmd_node(N_CMD, arg);
	io = new_parent_node(node_type, NULL, io);
	token_next(token);
	return (io);
}
