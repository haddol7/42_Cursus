/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:16:28 by daeha             #+#    #+#             */
/*   Updated: 2024/04/30 17:17:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void control_fildes(int fd_a[2], int fd_b[2], t_param arg, int n)
{
	if (n + arg.here_doc == arg.argc - 1)
		return ;
	if (n % 2 == 0)
	{
		if (n != 2)
		{
			close(fd_a[0]);
			close(fd_a[1]);
		}
		if (pipe(fd_a) == -1)
			terminate("pipex : pipe");
	}
	else
	{
		if (n != 3)
		{
			close(fd_b[0]);
			close(fd_b[1]);
		}
		if (pipe(fd_b) == -1)
			terminate("pipex: pipe");
	}
}
