/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:47:30 by daeha             #+#    #+#             */
/*   Updated: 2024/04/30 16:02:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{	
	if (argc < 5)
	{
		ft_putendl_fd("./pipex file1 cmd1 ... cmdn file2\n", 2);
		ft_putendl_fd("./pipex here_doc LIMITER cmd1 ... cmdn file2\n", 2);
		return (1);
	}
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8))
		here_doc(argv[2]);
	execute_procs(argv, envp);
	return (wait_proc());
}
