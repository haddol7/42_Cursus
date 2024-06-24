/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_and_or_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 02:26:24 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_status;

void	exec_and_or_if(t_node *node, t_stat *stat)
{
	int	origin[2];

	origin[INPUT] = dup(stat->fd[INPUT]);
	origin[OUTPUT] = dup(stat->fd[OUTPUT]);
	push_pipe_list(origin[INPUT], stat);
	push_pipe_list(origin[OUTPUT], stat);
	execution(node->left, stat);
	wait_pid_list(stat);
	dup2(origin[INPUT], stat->fd[INPUT]);
	close(origin[INPUT]);
	dup2(origin[OUTPUT], stat->fd[OUTPUT]);
	close(origin[OUTPUT]);
	if (node->type == N_AND && g_status == EXIT_SUCCESS)
		execution(node->right, stat);
	else if (node->type == N_OR && g_status != EXIT_SUCCESS)
		execution(node->right, stat);
}
