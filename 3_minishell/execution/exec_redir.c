/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 19:01:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_bool	is_redir_in(t_node_type type);

static void	exec_subshell(t_node *node, t_stat *stat)
{
	dprintf(2, "sub node - IN : %d OUT : %d\n", stat->fd[0], stat->fd[1]);
}

//dprintf(2, "redir node %d(%s)- IN : %d OUT : %d\n", node->type, node->right->cmd[0], fd[0], fd[1]);
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
		else if (node->type == N_OUTPUT)
			stat->fd[OUTPUT] = output(node->right->cmd[0]);
		else if (node->type == N_APPEND)
			stat->fd[OUTPUT] = append(node->right->cmd[0]);
		else
			stat->fd[INPUT] = heredoc(node->right->cmd[0]);
	}
	if (node->left->type >= N_INPUT && node->left->type <= N_APPEND)
		exec_redir(node->left, stat);
	else if (node->left->type == N_SUBSHELL)
		exec_subshell(node->left, stat);
	else
		exec_cmd(node->left, stat);
}

static t_bool	is_redir_in(t_node_type type)
{
	if (type == N_INPUT || type == N_HERE_DOC)
		return (TRUE);
	return (FALSE);
}
