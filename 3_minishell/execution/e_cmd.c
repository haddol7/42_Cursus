/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:02:12 by daeha             #+#    #+#             */
/*   Updated: 2024/06/10 21:00:37 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int g_status;

static void	exec_proc(char **arg, t_stat *stat);
static void	close_pipe_fds(t_stat *stat);
static void	set_arg_path(char **cmd, t_env *envp);
static char	*match_absolute_path(char *cmd, char **path);

//TODO: expand = expand(node->cmd)
//TODO: signal 작업
void	exec_cmd(t_node *node, t_stat *stat)
{
	int		pid;

	pid = fork();
	if (!pid)
		exec_proc(node->cmd, stat);
	else
	{
		push_pid_list(pid, stat);
		if (stat->fd[INPUT] != STDIN_FILENO)
			close(stat->fd[INPUT]);
		if (stat->fd[OUTPUT] != STDOUT_FILENO)
			close(stat->fd[OUTPUT]);
	}
}

static void	exec_proc(char **arg, t_stat *stat)
{
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
	set_arg_path(&arg[0], stat->envp);
	execve(arg[0], arg, NULL);
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

//TODO : t_env 완성 전
static void	set_arg_path(char **cmd, t_env *envp)
{
	int		i;
	char	**path;
	char	*new_cmd;

	i = 0;
	if (ft_strchr(*cmd, '/') == NULL)
	{
		// path = ft_split(env_find_value(envp, "PATH"), ':');
		path = ft_split("/Users/daeha/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/daeha/.brew/bin:", ':');
		new_cmd = match_absolute_path(*cmd, path);
		while (path[i])
			free(path[i]);
		free(path);
	}
	else
		new_cmd = match_relative_path(*cmd);
	free(*cmd);
	*cmd = new_cmd;
}

//1. /bin/echo
//2. ../echo
//3. ./echo
//4. ../../../../../../test/test
//3. echo/test
static char *match_relative_path(char *cmd)
{
	
}

static char	*match_absolute_path(char *cmd, char **path)
{
	char	*new_cmd;
	char	*cmd_slash;
	int		i;

	i = 0;
	cmd_slash = ft_strjoin("/", cmd);
	while (path && path[i] != NULL)
	{	
		new_cmd = ft_strjoin(path[i], cmd_slash);
		if (!access(new_cmd, F_OK | X_OK))
		{
			free(cmd_slash);
			return (new_cmd);
		}
		free(new_cmd);
		i++;
	}
	free(cmd_slash);
	error_cmd_not_found(cmd);
	return (NULL);
}
