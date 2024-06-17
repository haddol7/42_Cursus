/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/14 23:25:30 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

# include "libft.h"
# include "parser.h"
# include "expansion.h"
# include "tokenizer.h"
# include "builtin.h"
# include "execution.h"

typedef struct s_minishell
{
	t_node	*ast;
	t_token	*token;
	t_stat	stat;
}	t_minishell;

#endif
