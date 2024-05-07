/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:47:30 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 22:10:06 by daeha            ###   ########.fr       */
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
		return (1);
	}
	if (argc >= 6 && ft_strlen(argv[1]) == 8 && \
		!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		arg.here_doc = 1;
		arg.doc_name = here_doc(argv[2]);
	}
	execute_procs(arg, argc);
	return (wait_proc(arg));
}

static void	init_param(t_param *arg, int argc, char *argv[], char *envp[])
{
	arg->argc = argc;
	arg->argv = argv;
	arg->envp = envp;
	arg->doc_name = NULL;
	arg->here_doc = 0;
}
