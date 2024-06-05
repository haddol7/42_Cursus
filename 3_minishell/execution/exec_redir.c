/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/05 16:34:52 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	exec_subshell(t_node *node, int fd[2])
{
	dprintf(2, "sub node - IN : %d OUT : %d\n", fd[0], fd[1]);
}

static void	exec_cmd(t_node *node, int fd[2])
{
	dprintf(2, "cmd node - IN : %d OUT : %d\n", fd[0], fd[1]);
}

void	exec_redir(t_node *node, int fd[2])
{
	int	fd_heredoc;

	if (node->type == N_HERE_DOC)
		fd_heredoc = heredoc(node->right->cmd[0]);
	if (fd[INPUT] != -1 && fd[OUTPUT] != -1)
	{
		if (node->type == N_INPUT || node->type == N_HERE_DOC)
			close(fd[INPUT]);
		else
			close(fd[OUTPUT]);
		if (node->type == N_INPUT)
			fd[INPUT] = input(node->right->cmd[0]);
		else if (node->type == N_OUTPUT)
			fd[OUTPUT] = output(node->right->cmd[0]);
		else if (node->type == N_APPEND)
			fd[OUTPUT] = append(node->right->cmd[0]);
		else
			fd[INPUT] = fd_heredoc;
	}
	dprintf(2, "redir node %d(%s)- IN : %d OUT : %d\n", node->type, node->right->cmd[0], fd[0], fd[1]);
	if (node->left->type >= N_INPUT && node->left->type <= N_APPEND)
		exec_redir(node->left, fd);
	else if (node->left->type == N_SUBSHELL)
		exec_subshell(node->left, fd);
	else
		exec_cmd(node->left, fd);
}
