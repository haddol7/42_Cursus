/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:01 by daeha             #+#    #+#             */
/*   Updated: 2024/06/24 23:09:02 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_pipe(t_node *node, t_stat *stat)
{
	int	fd[2];
	int	origin[2];

	pipe(fd);
	origin[INPUT] = stat->fd[INPUT];
	origin[OUTPUT] = stat->fd[OUTPUT];
	if (stat->fd_pipe != -1 && stat->fd_pipe != 1 && stat->fd_pipe != 0)
		stat->fd_dump[stat->n_dump++] = stat->fd_pipe;
	stat->fd_dump[stat->n_dump++] = fd[INPUT];
	stat->fd_pipe = fd[OUTPUT];
	stat->fd[OUTPUT] = fd[OUTPUT];
	execution(node->left, stat);
	close(fd[OUTPUT]);
	stat->fd_pipe = fd[INPUT];
	if (stat->fd[INPUT] != origin[INPUT] && stat->fd[INPUT] != STDIN_FILENO)
		close(stat->fd[INPUT]);
	stat->fd[INPUT] = fd[INPUT];
	if (stat->fd[OUTPUT] != fd[OUTPUT] && stat->fd[OUTPUT] != STDOUT_FILENO)
		close(stat->fd[OUTPUT]);
	stat->fd[OUTPUT] = origin[OUTPUT];
	execution(node->right, stat);
	close(fd[INPUT]);
	if (stat->fd[INPUT] == fd[INPUT])
		stat->fd[INPUT] = origin[INPUT];
	stat->fd_pipe = -1;
}
