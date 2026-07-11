/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:12:06 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 21:13:49 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{	
	if (argc != 5)
	{
		ft_putendl_fd("pipex : argc error", 2);
		return (1);
	}
	execute_procs(argv, envp);
	return (wait_proc());
}
