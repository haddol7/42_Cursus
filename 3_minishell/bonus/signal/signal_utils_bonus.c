/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:53:08 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_bonus.h"
#include "minishell_bonus.h"

extern int	g_signal;

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

void	sig_heredoc_parent(void)
{
	signal(SIGINT, kill_child);
}

void	sig_heredoc_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
	signal(SIGINT, exit_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
