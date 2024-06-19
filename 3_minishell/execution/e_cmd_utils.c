/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:10:55 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 22:47:39 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_status;

void	error_cmd_exit(char *cmd, int error_type)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error_type == EVALUE)
	{
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
	}
	else
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (error_type != EVALUE && error_type != ENOCMD)
		ft_putendl_fd(strerror(error_type), STDERR_FILENO);
	else if (error_type == EVALUE)
		ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	else
		ft_putendl_fd("command not found", STDERR_FILENO);
	if (error_type == ENOENT || error_type == ENOCMD)
		exit(127);
	else if (error_type == EACCES || error_type == EISDIR)
		exit(126);
}

t_bool	redirect_to_cmd(t_stat *stat, t_bool is_forked)
{
	if (stat->fd[INPUT] == -1 || stat->fd[OUTPUT] == -1)
	{
		if (stat->fd[INPUT] != -1 && stat->fd[INPUT] != STDIN_FILENO)
			close(stat->fd[INPUT]);
		if (stat->fd[OUTPUT] != -1 && stat->fd[INPUT] != STDOUT_FILENO)
			close(stat->fd[OUTPUT]);
		if (is_forked)
			exit(EXIT_FAILURE);
		else
			return (FALSE);
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
	return (TRUE);
}

void	close_pipe_fds(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->n_pipe)
	{
		if (stat->pipe[i] != stat->fd[INPUT] \
			&& stat->pipe[i] != stat->fd[OUTPUT])
			close(stat->pipe[i]);
		i++;
	}
}

void	if_not_executable_then_exit(char *file, char *cmd)
{
	struct stat	buf;

	stat(file, &buf);
	if (access(file, F_OK))
		error_cmd_exit(cmd, ENOENT);
	else if (access(file, X_OK))
		error_cmd_exit(cmd, EACCES);
	else if ((buf.st_mode & S_IFMT) == S_IFDIR)
		error_cmd_exit(cmd, EISDIR);
}

char	*change_as_absolute_path(char *cmd)
{
	size_t		str_len;
	size_t		file_len;
	char		*file;
	char		*path;
	char		*ret;

	str_len = ft_strlen(cmd) - 1;
	file_len = 0;
	while (cmd[str_len - file_len] != '/')
		file_len++;
	path = (char *)ft_malloc(sizeof(char) * (str_len - file_len + 1));
	file = (char *)ft_malloc(sizeof(char) * (file_len + 2));
	ft_strlcpy(path, cmd, str_len - file_len + 1);
	ft_strlcpy(file, cmd + str_len - file_len, file_len + 2);
	if (chdir(path) == -1)
		error_cmd_exit(cmd, ENOENT);
	free(path);
	path = getcwd(NULL, 0);
	ret = ft_strjoin(path, file);
	free(file);
	return (ret);
}
