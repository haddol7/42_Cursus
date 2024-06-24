/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_and_or_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/24 23:56:51 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	exec_and_or_if(t_node *node, t_stat *stat)
{
	int	*status;

	execution(node->left, stat);
	wait_pid_list(stat);
	status = get_status();
	if (node->type == N_AND && *status == EXIT_SUCCESS)
		execution(node->right, stat);
	else if (node->type == N_OR && *status != EXIT_SUCCESS)
		execution(node->right, stat);
}
