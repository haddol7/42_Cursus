/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:16:00 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 22:57:37 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

extern int	g_status;

void	show_new_prompt(int signal)
{
	(void) signal;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

void	exit_forked(int signal)
{
	if (signal == SIGINT)
		ft_putendl_fd("", STDOUT_FILENO);
	else if (signal == SIGQUIT)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
}

void	exit_heredoc(int signal)
{
	(void) signal;
	ft_putendl_fd("", STDOUT_FILENO);
	exit(1);
}
