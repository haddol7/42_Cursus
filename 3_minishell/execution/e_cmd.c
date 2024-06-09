/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:02:12 by daeha             #+#    #+#             */
/*   Updated: 2024/06/07 23:57:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"

extern int g_status;

static void	exec_proc(char **arg, t_stat *stat);
static void	close_pipe_fds(t_stat *stat);
//TODO: expand = expand(node->cmd)
//TODO: 실행 파일 경로 찾는 함수
//TODO: signal 작업

void	exec_cmd(t_node *node, t_stat *stat)
{
	int		pid;

	pid = fork();
	if (!pid)
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

//dprintf(2, "cmd node - %s : %d OUT : %d\n", arg[1], stat->fd[0], stat->fd[1]);
static void	exec_proc(char **arg, t_stat *stat)
{
	char	**cmd;

	cmd = arg;
	close_pipe_fds(stat);
	if (stat->fd[INPUT] == -1 || stat->fd[OUTPUT] == -1)
	{
		if (stat->fd[INPUT] != -1 && stat->fd[INPUT] != STDIN_FILENO)
			close(stat->fd[INPUT]);
		if (stat->fd[OUTPUT] != -1 && stat->fd[INPUT] != STDOUT_FILENO)
			close(stat->fd[OUTPUT]);
		exit(EXIT_FAILURE);
	}
	if (stat->fd[OUTPUT] != STDOUT_FILENO)
	{
		dup2(stat->fd[OUTPUT], STDOUT_FILENO);
		close(stat->fd[OUTPUT]);
	}
	if (stat->fd[INPUT] != STDIN_FILENO)
	{
		dup2(stat->fd[INPUT], STDIN_FILENO);
		close(stat->fd[INPUT]);
	}
	execve("/bin/echo", cmd, NULL);
	exit(EXIT_FAILURE);
}

static void	close_pipe_fds(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->n_pipe)
	{
		if (stat->pipe[i] != stat->fd[0] && stat->pipe[i] != stat->fd[1])
			close(stat->pipe[i]);
		i++;
	}
}
