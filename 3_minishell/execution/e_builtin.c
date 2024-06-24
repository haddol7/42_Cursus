/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:40:58 by daeha             #+#    #+#             */
/*   Updated: 2024/06/24 23:59:02 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"
#include "minishell.h"

static void	exec_forked_builtin(t_node *node, t_stat *stat);
static void	exec_builtin_func(t_node *node, t_stat *stat);

t_bool	is_builtin(char *arg)
{
	size_t	len;

	if (arg == NULL)
		return (FALSE);
	len = ft_strlen(arg);
	if (len == 2 && !ft_strncmp(arg, "cd", 2))
		return (TRUE);
	else if (len == 3 && !ft_strncmp(arg, "env", 3))
		return (TRUE);
	else if (len == 3 && !ft_strncmp(arg, "pwd", 3))
		return (TRUE);
	else if (len == 4 && !ft_strncmp(arg, "echo", 4))
		return (TRUE);
	else if (len == 4 && !ft_strncmp(arg, "exit", 4))
		return (TRUE);
	else if (len == 5 && !ft_strncmp(arg, "unset", 5))
		return (TRUE);
	else if (len == 6 && !ft_strncmp(arg, "export", 6))
		return (TRUE);
	else
		return (FALSE);
}

void	exec_builtin(t_node *node, t_stat *stat)
{
	int		std[2];

	if (stat->fd_pipe != -1)
		exec_forked_builtin(node, stat);
	else
	{	
		std[INPUT] = dup(STDIN_FILENO);
		std[OUTPUT] = dup(STDOUT_FILENO);
		if (redirect_to_cmd(stat, FALSE))
			exec_builtin_func(node, stat);
		dup2(std[INPUT], STDIN_FILENO);
		dup2(std[OUTPUT], STDOUT_FILENO);
		close(std[INPUT]);
		close(std[OUTPUT]);
	}
}

static void	exec_forked_builtin(t_node *node, t_stat *stat)
{
	pid_t	pid;
	int		*status;

	sig_forked_mode();
	pid = fork();
	if (!pid)
	{	
		close_dump_fds(stat);
		redirect_to_cmd(stat, TRUE);
		exec_builtin_func(node, stat);
		status = get_status();
		exit(*status);
	}
	else
	{
		push_pid_list(pid, stat);
		if (stat->fd[INPUT] != STDIN_FILENO)
			close(stat->fd[INPUT]);
		if (stat->fd[OUTPUT] != STDOUT_FILENO)
			close(stat->fd[OUTPUT]);
	}
}

static void	exec_builtin_func(t_node *node, t_stat *stat)
{	
	char	*file;
	size_t	len;

	file = node->cmd[0];
	len = ft_strlen(file);
	if (len == 2 && !ft_strncmp(file, "cd", 2))
		ms_cd(node->cmd, stat->envp);
	else if (len == 3 && !ft_strncmp(file, "env", 3))
		ms_env(node->cmd, stat->envp);
	else if (len == 3 && !ft_strncmp(file, "pwd", 3))
		ms_pwd();
	else if (len == 4 && !ft_strncmp(file, "echo", 4))
		ms_echo(node->cmd);
	else if (len == 4 && !ft_strncmp(file, "exit", 4))
		ms_exit(node->cmd);
	else if (len == 5 && !ft_strncmp(file, "unset", 5))
		ms_unset(node->cmd, stat->envp);
	else
		ms_export(node->cmd, stat->envp);
}
