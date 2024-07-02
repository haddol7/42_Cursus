/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:01 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "execution_bonus.h"

static void	ft_pipe(int fd[2]);
static void	fd_copy(int origin[2], t_stat *stat);

void	exec_pipe(t_node *node, t_stat *stat)
{
	int	fd[2];
	int	origin[2];

	ft_pipe(fd);
	fd_copy(origin, stat);
	if (stat->fd_pipe != -1 && stat->fd_pipe != 1 && stat->fd_pipe != 0)
		push_pipe_list(stat->fd_pipe, stat);
	push_pipe_list(fd[INPUT], stat);
	stat->fd_pipe = fd[OUTPUT];
	stat->fd[OUTPUT] = fd[OUTPUT];
	execution(node->left, stat);
	stat->n_dump--;
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

void	push_pipe_list(int fd, t_stat *stat)
{
	stat->fd_dump[stat->n_dump++] = fd;
	if (stat->n_dump == MAX_PIPE)
	{	
		ft_putendl_fd("minishell : maximum number of pipe exceeded", \
					STDERR_FILENO);
		wait_pid_list(stat);
		stat->n_pid = PROC_EXCEED;
		set_status(EXIT_FAILURE);
		return ;
	}
}

static void	fd_copy(int origin[2], t_stat *stat)
{
	origin[INPUT] = stat->fd[INPUT];
	origin[OUTPUT] = stat->fd[OUTPUT];
}

static void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		fd[INPUT] = -1;
		fd[OUTPUT] = -1;
	}
}
