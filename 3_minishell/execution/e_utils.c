/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:04:44 by daeha             #+#    #+#             */
/*   Updated: 2024/06/11 17:20:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int g_status;

void	push_pid_list(pid_t pid, t_stat *stat)
{
	stat->pid[stat->n_pid++] = pid;
	//printf("pid %d\n", stat->pid[stat->n_pid - 1]);
}

//TODO: g_status 관리
void	wait_pid_list(t_stat *stat)
{
	while (stat->n_pid >= 0)
	{
		//printf("pid : %d ", stat->pid[stat->n_pid - 1]);
		waitpid(stat->pid[--stat->n_pid], &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		// printf("g_status : %d\n", g_status);
	}
}
