/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:02:12 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 19:33:28 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"

extern int g_status;

//TODO: expand = expand(node->cmd)
static void	exec_proc(char **arg, t_stat *stat)
{
	char	**cmd;
	int		input;
	int		output;

	cmd = arg;
	if (stat->fd[INPUT] == -1 || stat->fd[OUTPUT] == -1)
	{
		if(stat->fd[INPUT] != -1 && stat->fd[INPUT] != STDIN_FILENO)
			close(stat->fd[INPUT]);
		if (stat->fd[OUTPUT] != -1 && stat->fd[INPUT] != STDOUT_FILENO)
			close(stat->fd[OUTPUT]);
		exit(EXIT_FAILURE);
	}
	if (stat->fd[INPUT] != STDIN_FILENO)
	{
		dup2(stat->fd[INPUT], STDIN_FILENO);
		close(stat->fd[INPUT]);
	}
	if (stat->fd[OUTPUT] != STDOUT_FILENO)
	{
		dup2(stat->fd[OUTPUT], STDOUT_FILENO);
		close(stat->fd[OUTPUT]);
	}
	execve("/bin/cat", cmd, NULL);
	exit(EXIT_FAILURE);
}

//	dprintf(2, "cmd node - IN : %d OUT : %d\n", fd[0], fd[1]);
void	exec_cmd(t_node *node, t_stat *stat)
{
	char	**expand;
	int		pid;

	pid = fork();
	if (pid == 0)
		exec_proc(node->cmd, stat);
	else
	{
		if (stat->fd[INPUT] != STDIN_FILENO)
			close(stat->fd[INPUT]);
		if (stat->fd[OUTPUT] != STDOUT_FILENO)
			close(stat->fd[OUTPUT]);
		waitpid(pid, &g_status, 0); 
	}
}
