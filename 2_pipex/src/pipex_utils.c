/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:28:07 by daeha             #+#    #+#             */
/*   Updated: 2024/04/28 16:11:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_param(t_pipe *fds, t_param *param)
{
	if (pipe(fds->a) == -1)
		terminate("pipe error");
	if (pipe(fds->b) == -1)
		terminate("pipe error");
	parse_envp_path(param->envp, param->path);
}

void	parse_envp_path(char *envp[], t_list *path)
{
	
}

void	terminate(char *msg)
{
	perror(msg);
	exit(1);
}
