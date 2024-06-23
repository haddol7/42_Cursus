/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:53:08 by daeha             #+#    #+#             */
/*   Updated: 2024/06/23 20:33:56 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

// void	handle_sig(int sig_int, int sig_quit, int term)
// {
// 	struct termios	term_set;

// 	tcgetattr(STDIN_FILENO, &term_set);
// 	if (term == 1)
// 		term_set.c_lflag &= ~ECHOCTL;
// 	else
// 		term_set.c_lflag |= ECHOCTL;
// 	tcsetattr(STDIN_FILENO, 0, &term_set);
// 	if (sig_int == DFL)
// 		signal(SIGINT, SIG_DFL);
// 	if (sig_int == IGN)
// 		signal(SIGINT, SIG_IGN);
// 	if (sig_int == HAN)
// 		signal(SIGINT, show_new_prompt);
// 	if (sig_quit == DFL)
// 		signal(SIGQUIT, SIG_DFL);
// 	if (sig_quit == IGN)
// 		signal(SIGQUIT, SIG_IGN);
// 	if (sig_quit == HAN)
// 		signal(SIGQUIT, exit_forked);
// }

void	sig_prompt_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
	signal(SIGINT, show_new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_parent_mode(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_forked_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_heredoc_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
