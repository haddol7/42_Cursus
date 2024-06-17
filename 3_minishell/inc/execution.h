/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/17 23:11:22 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include "parser.h"
# include "expansion.h"

# define MAX_PIPE 1024
# define MAX_PID 512

# define READ 0
# define WRITE 1
# define INPUT 0
# define OUTPUT 1

# define ENOCMD 0
# define ENOENT 2
# define EACCES 13
# define EISDIR 21
# define EVALUE 1

typedef struct s_stat
{
	struct s_env	*envp;
	int				fd[2];
	int				pid[MAX_PID];
	int				n_pid;
	int				pipe[MAX_PIPE];
	int				n_pipe;
	t_bool			is_pipe;
}	t_stat;

//e_execution.c
void	execution(t_node *node, t_stat *stat);

//e_and_of_if.c
void	exec_and_or_if(t_node *node, t_stat *stat);

//e_builtin.c
t_bool	is_builtin(char *arg);
void	exec_builtin(t_node *node, t_stat *stat);

//e_cmd.c
void	exec_cmd(t_node *node, t_stat *stat);

//e_cmd_utils.c
void	error_cmd_exit(char *cmd, int error_type);
t_bool	redirect_to_cmd(t_stat *stat, t_bool is_forked);
void	close_pipe_fds(t_stat *stat);
void	if_not_executable_then_exit(char *file, char *cmd);
char	*change_as_absolute_path(char *cmd);

//e_pipe.c
void	exec_pipe(t_node *node, t_stat *stat);

//e_redir.c
void	exec_redir(t_node *node, t_stat *stat);

//e_redir_here_doc.c
void	exec_here_doc(t_node *node);

//e_redir_utils.c
void	error_redir(char *name);
int		input(char *filename);
int		append(char *filename);
int		output(char *filename);
int		heredoc(char *filename);

//e_subshell.c
void	exec_subshell(t_node *node, t_stat *stat);

//e_utils.c
void	push_pid_list(pid_t pid, t_stat *stat);
void	wait_pid_list(t_stat *stat);
char	*env_find_value(char *key, t_env *envp);
t_env	*env_find_pointer(char *key, t_env *envp);

#endif
