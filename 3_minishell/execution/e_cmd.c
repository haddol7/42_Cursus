/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:02:12 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 22:47:45 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"

extern int g_status;

//TODO: expand = expand(node->cmd)
//TODO: 실행 파일 경로 찾는 함수
//TODO: signal 작업
static void	exec_proc(char **arg, t_stat *stat)
{
	char	**cmd;
	int		input;
	int		output;

	cmd = arg;
	if (stat->fd[INPUT] == -1 || stat->fd[OUTPUT] == -1)
	{
		if (stat->fd[INPUT] != -1 && stat->fd[INPUT] != STDIN_FILENO)
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
	dprintf(2, "cmd node - IN : %d OUT : %d\n", stat->fd[0], stat->fd[1]);
	execve("/bin/sleep", cmd, NULL);
	exit(EXIT_FAILURE);
}

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
		push_pid_list(pid, stat);
	}
}
