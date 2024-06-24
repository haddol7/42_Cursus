/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_and_or_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 00:00:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_status;

void	exec_and_or_if(t_node *node, t_stat *stat)
{	
	int	origin[2];

	origin[INPUT] = stat->fd[INPUT];
	origin[OUTPUT] = stat->fd[OUTPUT];
	execution(node->left, stat);
	wait_pid_list(stat);
	if (stat->fd[INPUT] != STDIN_FILENO && stat->fd[INPUT] != origin[INPUT])
	{
		close(stat->fd[INPUT]);
		stat->fd[INPUT] = origin[INPUT];
	}
	if (stat->fd[OUTPUT] != STDOUT_FILENO && stat->fd[OUTPUT] != origin[OUTPUT])
	{
		close(stat->fd[OUTPUT]);
		stat->fd[OUTPUT] = origin[OUTPUT];
	}
	if (node->type == N_AND && g_status == EXIT_SUCCESS)
		execution(node->right, stat);
	else if (node->type == N_OR && g_status != EXIT_SUCCESS)
		execution(node->right, stat);
}
