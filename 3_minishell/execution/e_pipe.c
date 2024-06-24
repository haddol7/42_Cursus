/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:01 by daeha             #+#    #+#             */
/*   Updated: 2024/06/24 20:07:15 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	push_pipe_list(int fd[2], t_stat *stat);

void	exec_pipe(t_node *node, t_stat *stat)
{
	int	fd[2];
	int	origin[2];

	pipe(fd);
	origin[INPUT] = stat->fd[INPUT];
	origin[OUTPUT] = stat->fd[OUTPUT];

	if (stat->fd_pipe != -1 && stat->fd_pipe != STDOUT_FILENO && stat->fd_pipe != STDIN_FILENO)
		stat->fd_dump[stat->n_dump++] = stat->fd_pipe;
	stat->fd_dump[stat->n_dump++] = fd[INPUT];
	stat->fd_pipe = fd[OUTPUT];
	stat->fd[OUTPUT] = fd[OUTPUT];
	//printf("left-pipe - %d %d \n", stat->fd[INPUT], stat->fd[OUTPUT]);
	execution(node->left, stat);


	close(fd[OUTPUT]);
	stat->fd_pipe = fd[INPUT];
	stat->fd[INPUT] = fd[INPUT];
	stat->fd[OUTPUT] = origin[OUTPUT];
	//printf("right-pipe - %d %d \n", stat->fd[INPUT], stat->fd[OUTPUT]);
	execution(node->right, stat);
	
	
	close(fd[INPUT]);
	stat->fd[INPUT] = origin[INPUT];
	stat->fd_pipe = -1;
}

static void	push_pipe_list(int fd[2], t_stat *stat)
{
	//dummy
	if (fd[0] == 1020)
	{
		stat->fd_dump[stat->n_dump++] = fd[OUTPUT];
		stat->fd_dump[stat->n_dump++] = fd[INPUT];
	}
	if (stat->n_dump == MAX_PIPE)
	{
		ft_putendl_fd("minishell : maximum number of process exceeded", \
					STDERR_FILENO);
		wait_pid_list(stat);
		ft_putendl_fd("exit...", STDERR_FILENO);
	}
}
