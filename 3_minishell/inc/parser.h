/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:54:45 by daeha             #+#    #+#             */
/*   Updated: 2024/05/25 19:44:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

typedef enum e_node_type
{
	N_CMD,
	N_AND,
	N_OR,
	N_PIPE,
	N_SUBSHELL,
	N_INPUT,
	N_OUTPUT,
	N_HERE_DOC,
	N_APPEND
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			**cmd;
	struct t_node	*left;
	struct t_node	*right;
}	t_node;

t_node	*parser(t_token *token);

#endif
