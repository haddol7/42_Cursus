/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:04:36 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 22:06:06 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"

# define READ 0
# define WRITE 1

//pipex_utils.c
void	terminate(char *msg);
void	parent_error(int n);
char	*extract_first_command(char *cmd);
int		wait_proc(void);

//exec_proc.c
void	execute_procs(char *argv[], char *envp[]);

#endif
