/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:06:05 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 02:54:39 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_bool	is_node_redir(t_node_type type);

void	execution(t_node *node, t_stat *stat)
{
	if (node == NULL)
		return ;
	if (node->type == N_AND || node->type == N_OR)
		exec_and_or_if(node, stat);
	else if (node->type == N_CMD && node->cmd != NULL)
		exec_cmd(node, stat);
	else if (node->type == N_PIPE)
		exec_pipe(node, stat);
	else if (is_node_redir(node->type))
		exec_redir(node, stat);
	else if (node->type == N_SUBSHELL)
		exec_subshell(node, stat);
}

static t_bool	is_node_redir(t_node_type type)
{
	if (type == N_INPUT || type == N_HERE_DOC || \
		type == N_OUTPUT || type == N_APPEND)
		return (TRUE);
	return (FALSE);
}
