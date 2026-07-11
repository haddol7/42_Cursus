/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:09:53 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:44:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_BONUS_H
# define SIGNALS_BONUS_H

# define DFL 0
# define IGN 1
# define HAN 2

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include "libft.h"

void	show_new_prompt(int sig);
void	exit_forked(int sig);
void	exit_heredoc(int sig);
void	kill_child(int signal);

void	sig_prompt_mode(void);
void	sig_forked_mode(void);
void	sig_heredoc_parent(void);
void	sig_heredoc_mode(void);
void	sig_parent_mode(void);

#endif
