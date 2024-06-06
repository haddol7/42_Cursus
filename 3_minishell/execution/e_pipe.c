/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:01 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 22:40:34 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_pipe(t_node *node, t_stat *stat)
{
	int fd[2];
	int	prev[2];

	prev[INPUT] = stat->fd[INPUT];
	prev[OUTPUT] = stat->fd[OUTPUT];
	pipe(fd);
	stat->fd[OUTPUT] = fd[OUTPUT];
	execution(node->left, stat);
	stat->fd[OUTPUT] = prev[OUTPUT];
	stat->fd[INPUT] = fd[INPUT];
	execution(node->right, stat);
}
