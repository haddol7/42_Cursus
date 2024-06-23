/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:53:08 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 23:22:12 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_bonus.h"

void	sig_prompt_mode(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, 0, &term);
	signal(SIGINT, show_new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_forked_mode(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &term);
	signal(SIGINT, exit_forked);
	signal(SIGQUIT, exit_forked);
}

void	sig_heredoc_mode(void)
{
	signal(SIGINT, exit_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
