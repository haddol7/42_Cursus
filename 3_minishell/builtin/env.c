/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:51 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 19:05:11 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(char **arg, t_env *env)
{
	if (arg[1] != NULL)
		error_cmd_exit(arg[1], ENOENT);
	while (env)
	{
		if (env->complete == 0)
			continue;
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(env->value, STDOUT_FILENO);
		env = env->next;
	}
	exit(EXIT_SUCCESS);
}
