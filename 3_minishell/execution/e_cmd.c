/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:02:12 by daeha             #+#    #+#             */
/*   Updated: 2024/06/12 16:44:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_status;

static void	exec_proc(char **arg, t_stat *stat);
static void	set_arg_path(char **cmd, t_env *envp);
static char	*match_in_env_path(char *cmd, char **path);
static char	*match_in_current_path(char *cmd);

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
	redirect_to_cmd(stat);
	set_arg_path(&arg[0], stat->envp);
	execve(arg[0], arg, NULL);
	exit(EXIT_FAILURE);
}

//TODO : path = ft_split(env_find_value(envp, "PATH"), ':');
static void	set_arg_path(char **cmd, t_env *envp)
{
	int		i;
	char	**path;
	char	*file;

	i = 0;
	if (ft_strchr(*cmd, '/') == NULL)
	{
		path = ft_split("/Users/daeha/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/daeha/.brew/bin:", ':');
		file = match_in_env_path(*cmd, path);
		while (path[i])
			free(path[i++]);
		free(path);
	}
	else
		file = match_in_current_path(*cmd);
	if_not_executable_then_exit(file, *cmd);
	free(*cmd);
	*cmd = file;
}

static char	*match_in_current_path(char *cmd)
{	
	char	*file;
	char	*current_path;

	if (*cmd == '/')
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	current_path = getcwd(NULL, 0);
	file = change_as_absolute_path(cmd);
	chdir(current_path);
	if (!access(file, F_OK | X_OK))
		return (file);
	free(file);
	return (NULL);
}

//TODO : leaks 검사
static char	*match_in_env_path(char *cmd, char **path)
{
	char	*file;
	char	*cmd_slash;
	char	*cur_path;

	cmd_slash = ft_strjoin("/", cmd);
	while (path && *path != NULL)
	{	
		file = ft_strjoin(*path, cmd_slash);
		if (!access(file, F_OK | X_OK))
		{
			free(cmd_slash);
			return (file);
		}
		free(file);
		path++;
	}
	cur_path = getcwd(NULL, 0);
	file = ft_strjoin(cur_path, cmd_slash);
	free(cmd_slash);
	free(cur_path);
	if (!access(file, F_OK | X_OK))
		return (file);
	free(file);
	exit_cmd_error(cmd, ENOCMD);
	return (NULL);
}
