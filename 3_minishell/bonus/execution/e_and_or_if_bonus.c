/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_and_or_if_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "execution_bonus.h"

static void	save_pre_cmd_fd(int origin[2], t_stat *stat);
static void	restore_pre_cmd_fd(int origin[2], t_stat *stat);

void	exec_and_or_if(t_node *node, t_stat *stat)
{
	int	*status;
	int	origin[2];

	save_pre_cmd_fd(origin, stat);
	execution(node->left, stat);
	wait_pid_list(stat);
	restore_pre_cmd_fd(origin, stat);
	status = get_status();
	if (node->type == N_AND && *status == EXIT_SUCCESS)
		execution(node->right, stat);
	else if (node->type == N_OR && *status != EXIT_SUCCESS)
		execution(node->right, stat);
}

static void	save_pre_cmd_fd(int origin[2], t_stat *stat)
{
	origin[INPUT] = dup(stat->fd[INPUT]);
	origin[OUTPUT] = dup(stat->fd[OUTPUT]);
	push_pipe_list(origin[INPUT], stat);
	push_pipe_list(origin[OUTPUT], stat);
}

static void	restore_pre_cmd_fd(int origin[2], t_stat *stat)
{
	if (stat->fd[INPUT] == -1)
		stat->fd[INPUT] = origin[INPUT];
	else
	{
		dup2(origin[INPUT], stat->fd[INPUT]);
		close(origin[INPUT]);
	}
	if (stat->fd[OUTPUT] == -1)
		stat->fd[OUTPUT] = origin[OUTPUT];
	else
	{
		dup2(origin[OUTPUT], stat->fd[OUTPUT]);
		close(origin[OUTPUT]);
	}
}
