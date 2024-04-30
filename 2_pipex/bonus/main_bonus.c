/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:47:30 by daeha             #+#    #+#             */
/*   Updated: 2024/04/30 23:17:55 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_param(t_param *arg, int argc, char *argv[], char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{	
	t_param	arg;

	init_param(&arg, argc, argv, envp);
	if (argc < 5)
	{
		ft_putendl_fd("pipex : argc error", 2);
		ft_putendl_fd("./pipex file1 cmd1 ... cmdn file2", 2);
		ft_putendl_fd("./pipex here_doc LIMITER cmd1 ... cmdn file2", 2);
		return (1);
	}
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		arg.doc_name = here_doc(argv[2]);
	execute_procs(arg, argc);
	return (wait_proc(arg));
}

static void	init_param(t_param *arg, int argc, char *argv[], char *envp[])
{
	arg->argc = argc;
	arg->argv = argv;
	arg->envp = envp;
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8))
		arg->here_doc = 1;
	else
		arg->here_doc = 0;
}
