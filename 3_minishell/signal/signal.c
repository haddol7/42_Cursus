/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:16:00 by daeha             #+#    #+#             */
/*   Updated: 2024/06/23 20:33:48 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

extern int	g_status;

void	show_new_prompt(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", STDOUT_FILENO);//TODO err로 처처리리??
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

// void	exit_forked(int signal)
// {
// 	// struct termios	term;

// 	(void) signal;
// 	// tcgetattr(STDIN_FILENO, &term);
// 	// term.c_lflag |= ECHOCTL;
// 	// tcsetattr(STDIN_FILENO, 0, &term);
// 	// g_status = signal + 128;
// 	// exit(1);
// 	// if (signal == SIGINT)
// 	// 	ft_putendl_fd("", STDOUT_FILENO);
// 	// else if (signal == SIGQUIT)
// 	// 	ft_putendl_fd("Quit: 3", STDOUT_FILENO);
// }

// void	exit_heredoc(int signal)
// {
// 	(void) signal;
// 	ft_putendl_fd("", STDOUT_FILENO);
// 	exit(1);
// }
