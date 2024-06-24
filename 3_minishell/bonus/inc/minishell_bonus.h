/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 04:49:46 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "parser_bonus.h"
# include "expansion_bonus.h"
# include "tokenizer_bonus.h"
# include "builtin_bonus.h"
# include "execution_bonus.h"
# include "signals_bonus.h"

typedef struct s_minishell
{
	t_node	*ast;
	t_token	*token;
	t_stat	stat;
}	t_minishell;

void	free_all_nodes(t_minishell *ms);
void	save_status(int *pre_status);
void	execution_no_sig(t_node *node, t_stat *stat);
void	add_history_if_not_null(char *input);
int		*get_status(void);
void	set_status(int status);

#endif
