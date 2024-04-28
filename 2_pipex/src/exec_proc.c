/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:33:52 by daeha             #+#    #+#             */
/*   Updated: 2024/04/28 19:52:22 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipe_rotation(t_pipe *fds, int n);
static void	command_procs(t_pipe *fds, t_param param, int n);
static void	redirect_io(int r_fd[2], int w_fd[2], t_param param, int n);

void	execute_procs(t_pipe *fds, t_param param)
{
	int	pid;
	int	n;

	n = 1;
	while (++n + 1 < param.argc)
	{
		if (n > 2)
			pipe_rotation(fds, n);
		pid = fork();
		if (pid == -1)
		{
			//error handler
		}
		else if (pid == 0)
		{
			if (n % 2 == 0)
				command_proc(fds->a, fds->b, param, n);
			else
				command_proc(fds->b, fds->a, param, n);
		}
	}
}

static void	pipe_rotation(t_pipe *fds, int n)
{
	if (n % 2 == 1)
	{
		close(fds->a[0]);
		close(fds->a[1]);
		pipe(fds->a);
	}
	else
	{
		close(fds->b[0]);
		close(fds->b[1]);
		pipe(fds->b);
	}
}

static void	command_proc(int r_fd[2], int w_fd[2], t_param param, int n)
{
	char	*cmd_path;
	char	**cmd_argv;
	
	redirect_io(r_fd, w_fd, param, n);
	cmd_path = find_path(param.argv[n], param.path);
	cmd_argv = parse_command(param.argv[n]);
	if (execve(cmd_path, cmd_argv, param.envp) == -1)
		terminate("execve error");
}

static void	redirect_io(int r_fd[2], int w_fd[2], t_param param, int n)
{	
	int	fd_read;
	int	fd_write;
	
	if (n == 2)
	{
		fd_read = open(param.argv[1], O_RDONLY);
		if (fd_read == -1)
			terminate("open error");
		if (close(r_fd[READ] == -1))
			terminate("close error");
	}
	else
		fd_read = r_fd[READ];
	if (close(r_fd[WRITE]) == -1)
		terminate("close error");
	if (n == param.argc - 2)
	{
		fd_write = open(param.argv[param.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 755);
		if (fd_write == -1)
			terminate("open error");
		if (close(w_fd[WRITE] == -1))
			terminate("close error");
	}
	else
		fd_write = w_fd[WRITE];
	if (dup2(fd_read, STDIN_FILENO) == -1)
		terminate("dup2 error");
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		terminate("dup2 error");
}

char	*find_path(char *cmd, )

void	wait_proc(int argc)
{
	
}
