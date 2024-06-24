/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:26:30 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/24 21:08:22 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	free_all_nodes(t_minishell *ms)
{
	free_all_token(&ms->token);
	free_all_tree(&ms->ast);
}

void	save_status(int *pre_status)
{
	*pre_status = g_status;
	g_status = 0;
}

void	execution_no_sig(t_node *node, t_stat *stat)
{
	if (g_status != 128 + SIGINT)
		execution(node, stat);
}

void	add_history_if_not_null(char *input)
{
	if (input != NULL && input[0] != '\0')
		add_history(input);
}
