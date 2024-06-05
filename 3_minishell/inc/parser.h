/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:54:45 by daeha             #+#    #+#             */
/*   Updated: 2024/06/04 15:15:16 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "unistd.h"
# include "tokenizer.h"
# include "tree.h"
# include "libft.h"

//TODO : 지우기!
# include <stdio.h>

//parser.c
t_node *parser(t_token **token);

//p_grammer.c
t_node	*list(t_token **token);
t_node	*pipeline(t_token **token);
t_node	*command(t_token **token);
t_node	*subshell(t_token **token);
t_node	*simple_command(t_token **token);

//p_grammer_2.c
t_node	*redirect_list(t_token **token);
t_node	*io_redirect(t_token **token);

//p_node_utils.c
t_node	*new_parent_node(t_node_type type, t_node *left, t_node *right);
t_node	*new_cmd_node(t_node_type type, char **arg);
t_node	*link_redir_to_node(t_node *node, t_node *redir);
t_node	*append_redir_node(t_node *redir, t_token **token);
char 	**append_cmd_arg(char **arg, t_token **token);

//p_token_utils.c
t_bool	is_token_redir(t_token *token);
t_bool	is_token(t_token *token, t_token_type type);
void	token_next(t_token **token);

void	syntax_error_test(char *str);
#endif
