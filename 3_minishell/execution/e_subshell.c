/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_subshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:07 by daeha             #+#    #+#             */
/*   Updated: 2024/06/07 23:59:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int g_status;

void	exec_subshell(t_node *node, t_stat *stat)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		execution(node->left, stat);
		exit(g_status);
	}
	else
	{
		//printf("subshell pid : %d\n", pid);
		waitpid(pid, &g_status, 0);
	}
		//push_pid_list(pid, stat);
}
