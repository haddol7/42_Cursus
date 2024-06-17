/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/17 16:28:10 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_bool	is_redir_in(t_node_type type);

void	exec_redir(t_node *node, t_stat *stat)
{
	if (stat->fd[INPUT] != -1 && stat->fd[OUTPUT] != -1)
	{
		if (stat->fd[INPUT] != STDIN_FILENO && is_redir_in(node->type))
			close(stat->fd[INPUT]);
		else if (stat->fd[OUTPUT] != STDOUT_FILENO && !is_redir_in(node->type))
			close(stat->fd[OUTPUT]);
		if (node->type == N_INPUT)
			stat->fd[INPUT] = input(node->right->cmd[0]);
		else if (node->type == N_HERE_DOC)
			stat->fd[INPUT] = heredoc(node->right->cmd[0]);
		else if (node->type == N_OUTPUT)
			stat->fd[OUTPUT] = output(node->right->cmd[0]);
		else
			stat->fd[OUTPUT] = append(node->right->cmd[0]);
	}
	execution(node->left, stat);
}

static t_bool	is_redir_in(t_node_type type)
{
	if (type == N_INPUT || type == N_HERE_DOC)
		return (TRUE);
	return (FALSE);
}
