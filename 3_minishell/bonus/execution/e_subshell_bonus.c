/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_subshell_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:07 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 23:20:52 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

extern int	g_status;

void	exec_subshell(t_node *node, t_stat *stat)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{	
		stat->n_pid = 0;
		execution(node->left, stat);
		wait_pid_list(stat);
		exit(g_status);
	}
	else
	{
		push_pid_list(pid, stat);
		waitpid(pid, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = WTERMSIG(g_status) + 128;
	}
}
