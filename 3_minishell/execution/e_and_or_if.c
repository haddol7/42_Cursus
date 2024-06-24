/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_and_or_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/24 20:45:46 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_status;

void	exec_and_or_if(t_node *node, t_stat *stat)
{
	execution(node->left, stat);
	wait_pid_list(stat);
	if (node->type == N_AND && g_status == EXIT_SUCCESS)
		execution(node->right, stat);
	else if (node->type == N_OR && g_status != EXIT_SUCCESS)
		execution(node->right, stat);
}
