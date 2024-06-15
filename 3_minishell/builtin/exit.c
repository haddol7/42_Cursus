/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:48 by daeha             #+#    #+#             */
/*   Updated: 2024/06/16 06:55:46 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int g_status;

void	ms_exit(char **arg, t_env *stat)
{
	int	status;
	
	if (arg[1] == NULL)
		exit(EXIT_SUCCESS);
	else if (!is_valid_code(arg[1]))
	{
		ft_putendl_fd("minishell: numeric argument required", STDERR_FILENO);
	}
	else if (arg[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_status = EXIT_FAILURE;
		return ;
	}
	status = ft_atoi(arg[1]);
	if (status >= 0)
		status = status % 256;
	else
		status = 256 + (status % 256);
	exit(status);
}
