/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 18:51:24 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include "parser.h"

# define READ 0
# define INPUT 0
# define WRITE 1
# define OUTPUT 1
# define ERR_REDIR 1

typedef struct s_stat
{
	int	fd[2];
	//t_env envp;
	
} t_stat;

//redirection.c
void	redir_error(char *name);
int		input(char *filename);
int		append(char *filename);
int		output(char *filename);
int		heredoc(char *filename);

//exec_here_doc.c
void	exec_here_doc(t_node *node);

//exec_redir.c
void	exec_redir(t_node *node, t_stat *stat);

//exec_cmd.c
void	exec_cmd(t_node *node, t_stat *stat);

//exec_pipe.c

//exec_subshell.c

//exec_and_of_if.c

#endif
