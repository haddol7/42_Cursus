/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:04:44 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 22:44:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	push_pid_list(pid_t pid, t_stat *stat)
{
	stat->pid[stat->num_pid++] = pid;
	printf("pid %d\n", stat->pid[stat->num_pid - 1]);
}

void	wait_pid_list(t_stat *stat)
{
	while (stat->num_pid)
		waitpid(stat->pid[stat->num_pid--], 0, 0);
}
