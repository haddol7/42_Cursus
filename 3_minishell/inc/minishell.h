/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/26 21:02:48 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "parser.h"
# include "expansion.h"
# include "tokenizer.h"
# include "builtin.h"
# include "execution.h"
# include "signals.h"

typedef struct s_minishell
{
	t_node	*ast;
	t_token	*token;
	t_stat	stat;
}	t_minishell;

void	free_all_nodes(t_minishell *ms);
void	save_status(int *pre_status);
void	execution_with_sig_check(t_node *node, t_stat *stat);
void	add_history_if_not_null(char *input);
int		*get_status(void);
void	set_status(int status);
void	del_here_doc_tmp_file(t_node *node);

#endif
