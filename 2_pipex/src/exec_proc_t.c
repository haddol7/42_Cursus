/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:33:52 by daeha             #+#    #+#             */
/*   Updated: 2024/04/29 18:10:41 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipe_rotation(t_pipe *fds, int n);
static void	command_proc(int fd[2], t_param param, int n);
static void	redirect_io(int fd[2], t_param param, int n);
static char	*find_path(char *cmd, char **pathv);
static char	**parse_command(char *cmd, char *path);

void	execute_procs(int fd[2], t_param param)
{
	int	pid;
	int	i;

	i = 0;
	while (i < 2)
	{
		pid = fork();
		if (pid == -1)
			terminate("error");
		else if (pid == 0)
		{
			if (i == 0)
				command_proc(fd, param, 2);
			else
				command_proc(fd, param, 3);
		}
		i++;
	}
}

static void	command_proc(int fd[2], t_param param, int n)
{
	char	*cmd_path;
	char	**cmd_argv;
	
	redirect_io(fd, param, n);
	cmd_path = find_path(param.argv[n], param.path);
	cmd_argv = parse_command(param.argv[n], cmd_path);
	if (execve(cmd_path, cmd_argv, param.envp) == -1)
		terminate("as\n");
}

static void	redirect_io(int fd[2], t_param param, int n)
{	
	int	fd_read;
	int	fd_write;
	
	if (n == 2)
	{
		close(fd[READ]);
		fd_read = open(param.argv[1], O_RDONLY, 0666);
		if (fd_read == -1)
			terminate("open error 1");

		dup2(fd_read, STDIN_FILENO);
		close(fd_read);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
	}
	else
	{
		close(fd[WRITE]);
		fd_write = open(param.argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd_write == -1)
			terminate("open error 2");

		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		dup2(fd_write, STDOUT_FILENO);
		close(fd_write);
	}
}

static char	*find_path(char *cmd, char **pathv)
{
	char	*path;
	char	*tmp;
	char	*cmd_trim;

	int i = 0;
	while (cmd[i] != ' ')
		i++;
	cmd_trim = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(cmd_trim, cmd, i + 1);
	
	i = 0;
	while (pathv[i] != NULL)
	{
		if (!access(cmd_trim, F_OK | X_OK))
			return (cmd_trim);
		i++;
	}
	
	while (pathv != NULL)
	{	
		tmp = ft_strjoin("/", cmd_trim);
		path = ft_strjoin(*pathv, tmp);
		if (path == NULL)
			terminate("command not found");
		if (!access(path, F_OK | X_OK))
			return (path);
		free(tmp);
		free(path);
		pathv++;
	}
	return (NULL);
}

// {"/usr/bin/cmd", "-a", "-t", NULL}
static char	**parse_command(char *cmd, char *path)
{
	return ft_split(cmd, ' ');
}
