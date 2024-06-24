/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:26:30 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/25 02:49:53 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	free_all_nodes(t_minishell *ms)
{
	free_all_token(&ms->token);
	free_all_tree(&ms->ast);
}

void	execution_no_sig(t_node *node, t_stat *stat)
{
	if (g_signal != 128 + SIGINT)
		execution(node, stat);
}

void	add_history_if_not_null(char *input)
{
	if (input != NULL && input[0] != '\0')
		add_history(input);
}

int	*get_status(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

void	set_status(int status)
{
	int	*exit_status;

	exit_status = get_status();
	*exit_status = status;
}
