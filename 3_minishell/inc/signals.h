/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:09:53 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 22:40:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

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

void	sig_prompt_mode(void);
void	sig_forked_mode(void);
void	sig_heredoc_mode(void);
#endif
