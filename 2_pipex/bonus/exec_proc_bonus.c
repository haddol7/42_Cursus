/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:33:52 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 19:00:12 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	command_proc(int read[2], int write[2], t_param arg, int n);
static void	redirect_io(int read[2], int write[2], t_param arg, int n);
static void	redirect_file_io(int read[2], int write[2], t_param arg, int n);
static int	open_file_io(t_param arg, int n);

void	execute_procs(t_param arg, int argc)
{
	int		fd_a[2];
	int		fd_b[2];
	int		pid;
	int		n;

	n = 1;
	if (arg.here_doc == 1)
		argc--;
	while (++n < argc - 1)
	{
		control_fildes(fd_a, fd_b, arg, n);
		pid = fork();
		if (pid == -1)
			terminate("pipex: fork");
		else if (pid == 0)
		{
			if (n % 2 == 0)
				command_proc(fd_b, fd_a, arg, n);
			else
				command_proc(fd_a, fd_b, arg, n);
		}
	}
	close_remainder_fds(fd_a, fd_b, n);
}

static void	command_proc(int read[2], int write[2], t_param arg, int n)
{
	char	*cmd_path;
	char	**cmd_argv;
	char	**path;

	redirect_io(read, write, arg, n);
	path = parse_envp_path(arg.envp);
	if (arg.here_doc == 1)
		n++;
	cmd_path = find_path(arg.argv[n], path);
	cmd_argv = ft_split(arg.argv[n], ' ');
	if (execve(cmd_path, cmd_argv, arg.envp) == -1)
		terminate("pipex: execve");
}

static void	redirect_io(int read[2], int write[2], t_param arg, int n)
{	
	if (n == 2 || n + arg.here_doc == arg.argc - 2)
		return (redirect_file_io(read, write, arg, n));
	close(read[WRITE]);
	dup2(read[READ], STDIN_FILENO);
	close(read[READ]);
	close(write[READ]);
	dup2(write[WRITE], STDOUT_FILENO);
	close(write[WRITE]);
}

static void	redirect_file_io(int read[2], int write[2], t_param arg, int n)
{
	int	fd;

	fd = open_file_io(arg, n);
	if (n == 2)
	{
		close(write[READ]);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(write[WRITE], STDOUT_FILENO);
		close(write[WRITE]);
	}
	else
	{
		close(read[WRITE]);
		dup2(read[READ], STDIN_FILENO);
		close(read[READ]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

static int	open_file_io(t_param arg, int n)
{
	int	fd;

	if (n == 2 && arg.here_doc)
		fd = open(arg.doc_name, O_RDONLY, 0666);
	else if (n == 2)
		fd = open(arg.argv[1], O_RDONLY, 0666);
	else if (arg.here_doc)
		fd = open(arg.argv[arg.argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(arg.argv[arg.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1 && n == 2)
		terminate("pipex: input");
	else if (fd == -1)
		terminate("pipex: output");
	return (fd);
}
