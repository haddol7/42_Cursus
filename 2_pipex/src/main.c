/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:12:06 by daeha             #+#    #+#             */
/*   Updated: 2024/04/28 19:50:02 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// cmd1 == argv[2]
// cmdn == argv[argc - 2]
// 0 1 2 3 4
// $> ./pipex file1 cmd1 cmd2 file2

int main(int argc, char *argv[], char *envp[])
{
	t_pipe fds;
	t_param	param;
	
	param.argc = argc;
	param.argv = argv;
	param.envp = envp;
	param.path = NULL;
	if (argc < 5)
		terminate("test");
	// if (!ft_strncmp(argv[1], "here_doc", 9))
	// 	here_doc();
	init_param(&fds, &param);
	execute_procs(&fds, param);
//	wait_proc(&fds, argc);
	return (0);
}
