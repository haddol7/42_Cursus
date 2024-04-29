/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:28:07 by daeha             #+#    #+#             */
/*   Updated: 2024/04/29 16:11:43 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**parse_envp_path(char *envp[]);

void	init_param(int *fd, t_param *param)
{
	if (pipe(fd) == -1)
		terminate("pipe error");
	param->path = parse_envp_path(param->envp);
}

static char	**parse_envp_path(char *envp[])
{
	int		i;
	char	*str_path;
	
	i = 0;
	while (envp[i])
	{	
		if (!ft_strncmp(envp[i], "PATH=", 5))
			str_path = envp[i] + 5;
		i++;
	}
	return (ft_split(str_path, ':'));
}

void	terminate(char *msg)
{
	perror(msg);
	exit(1);
}
