/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_and_or_if_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 04:35:09 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "execution_bonus.h"

void	exec_and_or_if(t_node *node, t_stat *stat)
{
	int	*status;
	int	origin[2];

	origin[INPUT] = dup(stat->fd[INPUT]);
	origin[OUTPUT] = dup(stat->fd[OUTPUT]);
	push_pipe_list(origin[INPUT], stat);
	push_pipe_list(origin[OUTPUT], stat);
	execution(node->left, stat);
	wait_pid_list(stat);
	status = get_status();
	dup2(origin[INPUT], stat->fd[INPUT]);
	close(origin[INPUT]);
	dup2(origin[OUTPUT], stat->fd[OUTPUT]);
	close(origin[OUTPUT]);
	if (node->type == N_AND && *status == EXIT_SUCCESS)
		execution(node->right, stat);
	else if (node->type == N_OR && *status != EXIT_SUCCESS)
		execution(node->right, stat);
}
