/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/10 18:46:50 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include "parser.h"
# include "expansion.h"

# define MAX_PIPE 1024
# define MAX_PID 512
# define READ 0
# define WRITE 1
# define INPUT 0
# define OUTPUT 1

typedef struct s_stat
{
	int	fd[2];
	int	pid[MAX_PID];
	int	pipe[MAX_PIPE];
	int	n_pid;
	int	n_pipe;
	t_env *envp;
}	t_stat;

//e_execution.c
void	execution(t_node *node, t_stat *stat);

//e_and_of_if.c
void	exec_and_or_if(t_node *node, t_stat *stat);

//e_cmd.c
void	exec_cmd(t_node *node, t_stat *stat);

//e_pipe.c
void	exec_pipe(t_node *node, t_stat *stat);

//e_redir.c
void	exec_redir(t_node *node, t_stat *stat);

//e_redir_here_doc.c
void	exec_here_doc(t_node *node);

//e_redir_utils.c
void	redir_error(char *name);
int		input(char *filename);
int		append(char *filename);
int		output(char *filename);
int		heredoc(char *filename);

//e_subshell.c
void	exec_subshell(t_node *node, t_stat *stat);

//e_utils.c
void	error_cmd_not_found(char *cmd);
void	push_pid_list(pid_t pid, t_stat *stat);
void	wait_pid_list(t_stat *stat);
#endif
