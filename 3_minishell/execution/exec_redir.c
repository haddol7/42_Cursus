/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/05 15:36:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


static void exec_subshell(t_node *node, int fd[2])
{
	dprintf(2, "sub node - IN : %d OUT : %d\n", fd[0], fd[1]);
}

static void exec_cmd(t_node *node, int fd[2])
{
	dprintf(2, "cmd node - IN : %d OUT : %d\n", fd[0], fd[1]);
}

void	exec_redir(t_node *node, int fd[2])
{
	t_node	*left;
	char	*file;
	int		fd_heredoc;
	
	left = node->left;
	file = node->right->cmd[0];
	if (node->type == N_HERE_DOC)
		fd_heredoc = heredoc(file); 
	if (fd[INPUT] != -1 && fd[OUTPUT] != -1)
	{
		if (node->type == N_INPUT)
			fd[INPUT] = input(file);
		else if (node->type == N_OUTPUT)
			fd[OUTPUT] = output(file);
		else if (node->type == N_APPEND)
			fd[OUTPUT] = append(file);
		else
			fd[INPUT] = fd_heredoc;
	}

	dprintf(2, "redir node %d(%s)- IN : %d OUT : %d\n", node->type, file, fd[0], fd[1]);
	
	if (left->type >= N_INPUT && left->type <= N_APPEND)
		exec_redir(left, fd);
	else if (left->type == N_SUBSHELL)
		exec_subshell(left, fd);
	else
		exec_cmd(left, fd);
}
