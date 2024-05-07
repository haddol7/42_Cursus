/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:28:07 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 21:23:41 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	terminate(char *msg)
{
	perror(msg);
	exit(1);
}

void	fork_error(t_param arg, int n)
{
	int	i;

	i = 2;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
	if (arg.here_doc == 1)
		unlink(arg.doc_name);
	terminate("pipex : fork");
}

int	wait_proc(t_param arg)
{
	int	i;
	int	n;
	int	status;

	i = -1;
	if (arg.here_doc)
		n = arg.argc - 4;
	else
		n = arg.argc - 3;
	while (++i < n)
		wait(&status);
	if (arg.here_doc == 1)
		unlink(arg.doc_name);
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
