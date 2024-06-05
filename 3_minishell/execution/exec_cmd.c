/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:02:12 by daeha             #+#    #+#             */
/*   Updated: 2024/06/05 20:27:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int g_status;

static void	exec_proc(char **arg, int fd[2])
{
	char	**cmd;

	//TODO: expand = expand(node->cmd)
	cmd = arg;
	printf("exec_proc\n");
	if (fd[INPUT] != STDIN_FILENO)
	{
		dup2(fd[INPUT], STDIN_FILENO);
		close(fd[INPUT]);
	}
	if (fd[OUTPUT] != STDOUT_FILENO)
	{
		dup2(fd[OUTPUT], STDOUT_FILENO);
		close(fd[OUTPUT]);
	}
	execve("/bin/echo", cmd, NULL);
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_node *node, int fd[2])
{
	char	**expand;
	int		pid;

//	dprintf(2, "cmd node - IN : %d OUT : %d\n", fd[0], fd[1]);

	pid = fork();
	if (pid == 0)
		exec_proc(node->cmd, fd);
	else
	{
		if (fd[INPUT] != STDIN_FILENO)
			close(fd[INPUT]);
		if (fd[OUTPUT] != STDOUT_FILENO)
			close(fd[OUTPUT]);
		waitpid(pid, &g_status, 0); 
	}

}
