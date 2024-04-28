/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:33:52 by daeha             #+#    #+#             */
/*   Updated: 2024/04/28 22:23:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipe_rotation(t_pipe *fds, int n);
static void	command_proc(int r_fd[2], int w_fd[2], t_param param, int n);
static void	redirect_io(int r_fd[2], int w_fd[2], t_param param, int n);
static char	*find_path(char *cmd, char **pathv);
static char	**parse_command(char *cmd, char *path);

void	execute_procs(t_pipe *fds, t_param param)
{
	int	pid;
	int	n;

	n = 1;
	while (++n + 1 < param.argc)
	{
		// if (n > 2)
		// 	pipe_rotation(fds, n);
		pid = fork();
		if (pid == -1)
		{
			//error handler
		}
		else if (pid == 0)
		{
			if (n % 2 == 0)
			{
				//printf("%d!\n", n);
				command_proc(fds->a, fds->b, param, n);
			}
			else
			{
				//printf("%d~\n", n);
				command_proc(fds->b, fds->a, param, n);
			}
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
	cmd_argv = parse_command(param.argv[n], cmd_path);

	if (execve(cmd_path, cmd_argv, param.envp) == -1)
		terminate("as\n");
}

static void	redirect_io(int r_fd[2], int w_fd[2], t_param param, int n)
{	
	int	fd_read;
	int	fd_write;
	

	printf("%d-th %d %d | %d %d\n", n, r_fd[0], r_fd[1], w_fd[0], w_fd[1]);

	if (n == 2)
	{
		fd_read = open(param.argv[1], O_RDONLY);
		if (fd_read == -1)
			terminate("redirect_io open error : 1");
		// if (r_fd[READ] != 0)
		// 	close(r_fd[READ]);
	}
	else
		fd_read = r_fd[READ];
	
	if (n == param.argc - 2)
	{
		fd_write = open(param.argv[param.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd_write == -1)
			terminate("redirect_io open error : 2");
		// if (w_fd[WRITE] != 0)
		// 	close(w_fd[WRITE]);
	}
	else
		fd_write = w_fd[WRITE];

	printf("%d %d\n", fd_read, fd_write);
	// if (n == 3)
	// {
	// 	char buf[100];
	// 	read(3, buf, 100);
	// 	write(2, buf, 100);
	// }

	dup2(fd_read, STDIN_FILENO);
	dup2(fd_write, STDOUT_FILENO);

	close(3);
	close(4);
	close(5);
	// if (r_fd[WRITE] != 0)
	// 	close(r_fd[WRITE]);
	// if (w_fd[READ] != 0)
	// 	close(w_fd[READ]);
	// close(fd_read);
	// close(fd_write);
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
	while (pathv != NULL)
	{	
		tmp = ft_strjoin("/", cmd_trim);
		path = ft_strjoin(*pathv, tmp);
		if (path == NULL)
			terminate("malloc erorr!!");
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
