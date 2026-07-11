/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:28:07 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 22:06:06 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	terminate(char *msg)
{
	perror(msg);
	exit(1);
}

void	parent_error(int n)
{
	if (n == 1)
		wait(NULL);
	terminate("pipex : fork");
}

int	wait_proc(void)
{
	int	status;

	wait(&status);
	wait(&status);
	return (WEXITSTATUS(status));
}

char	*extract_first_command(char *cmd)
{
	char	*ret;
	int		i;

	i = 0;
	while (cmd[i] != ' ')
		i++;
	if (*cmd != '/')
	{
		ret = (char *)ft_malloc(sizeof(char) * (i + 2));
		ret[0] = '/';
		ft_strlcpy(ret + 1, cmd, i + 1);
	}
	else
	{
		ret = (char *)ft_malloc(sizeof(char) * (i + 1));
		ft_strlcpy(ret, cmd, i + 1);
	}
	return (ret);
}
