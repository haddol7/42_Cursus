/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:12:06 by daeha             #+#    #+#             */
/*   Updated: 2024/04/29 16:20:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_proc(t_pipe fds, int argc)
{
	int i;
	int	status;

	i = 3;
	close(3);
	close(4);

	while (i < argc)
	{
		wait(&status);
		i++;
	}
	if (WIFSIGNALED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	int fd[2];
	t_param	param;
	
	param.argc = argc;
	param.argv = argv;
	param.envp = envp;
	param.path = NULL;
	if (argc < 5)
		terminate("test");
	init_param(fd, &param);
	execute_procs(fd, param);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
