/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:04:44 by daeha             #+#    #+#             */
/*   Updated: 2024/06/12 22:04:52 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansion.h"

extern int	g_status;

void	push_pid_list(pid_t pid, t_stat *stat)
{
	if (stat->n_pid == MAX_PID - 1)
	{
		ft_putendl_fd("minishell : maximum number of process exceeded", \
					STDERR_FILENO);
		wait_pid_list(stat);
		ft_putendl_fd("exit...", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	stat->pid[stat->n_pid++] = pid;
}

//TODO: g_status 관리
void	wait_pid_list(t_stat *stat)
{
	while (stat->n_pid >= 0)
	{
		waitpid(stat->pid[--stat->n_pid], &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
	}
}

char	*env_find_value(char *key, t_env *envp)
{
	size_t	len_key;
	size_t	len_envp;

	len_key = ft_strlen(key);
	while (envp)
	{
		len_envp = ft_strlen(envp->key);
		if (len_key == len_envp && !ft_strncmp(key, envp->key, len_key))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}
