/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_subshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:07 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 20:28:44 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_subshell(t_node *node, t_stat *stat)
{
	dprintf(2, "subshell %d(%s)- IN : %d OUT : %d\n", node->type, node->right->cmd[0], stat->fd[0], stat->fd[1]);
}
