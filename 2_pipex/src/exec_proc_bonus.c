/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:33:52 by daeha             #+#    #+#             */
/*   Updated: 2024/04/30 16:03:03 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	command_proc(int fd[2], char *argv[], char *envp[], int n);
static void	redirect_io(int fd[2], char *argv[], int n);
static char	*find_path(char *cmd, char **pathv);
static char	**parse_envp_path(char *envp[]);

void	execute_procs(char *argv[], char *envp[])
{
	int		fd[2];
	int		pid;
	int		n;

	if (pipe(fd) == -1)
		terminate("pipex: pipe:");
	n = -1;
	while (++n < 2)
	{
		pid = fork();
		if (pid == -1)
			terminate("pipex: fork:");
		else if (pid == 0)
		{
			if (n % 2 == 0)
				command_proc(fd, argv, envp, n);
			else
				command_proc(fd, argv, envp, n);
		}
	}
	close(fd[0]);
	close(fd[1]);
}

static void	command_proc(int fd[2], char *argv[], char *envp[], int n)
{
	char	*cmd_path;
	char	**cmd_argv;
	char	**path;

	redirect_io(fd, argv, n);
	path = parse_envp_path(envp);
	cmd_path = find_path(argv[n + 2], path);
	cmd_argv = ft_split(argv[n + 2], ' ');
	if (execve(cmd_path, cmd_argv, envp) == -1)
		terminate("pipex: execve:");
}

static void	redirect_io(int fd[2], char *argv[], int n)
{	
	int	file;

	if (n == 0)
	{
		close(fd[READ]);
		file = open(argv[1], O_RDONLY, 0666);
		if (file == -1)
			terminate("pipex: input:");
		dup2(file, STDIN_FILENO);
		close(file);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
	}
	else
	{
		close(fd[WRITE]);
		file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (file == -1)
			terminate("pipex: output:");
		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
}

static char	*find_path(char *cmd, char **pathv)
{
	char	*path;
	char	*cmd_trim;
	int		i;

	i = -1;
	cmd_trim = extract_first_command(cmd);
	while (pathv[++i] != NULL)
	{
		if (!access(cmd_trim, F_OK | X_OK))
			return (cmd_trim);
	}
	while (pathv != NULL)
	{	
		path = ft_strjoin(*pathv, cmd_trim);
		if (!access(path, F_OK | X_OK))
			return (path);
		free(path);
		pathv++;
	}
	return (NULL);
}

static char	**parse_envp_path(char *envp[])
{
	int		i;
	char	*str_path;

	i = 0;
	while (envp[i])
	{	
		if (!ft_strncmp(envp[i], "PATH=", 5))
			str_path = envp[i] + 5;
		i++;
	}
	return (ft_split(str_path, ':'));
}
