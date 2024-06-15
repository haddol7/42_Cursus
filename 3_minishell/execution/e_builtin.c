/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:40:58 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 19:03:39 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"

t_bool	is_builtin_then_exec(char **arg, t_stat *stat)
{
	char	*file;
	size_t	len;

	file = arg[0];
	len = ft_strlen(file);
	if (len == 2 && !ft_strncmp(file, "cd", 2))
		ms_cd(arg, stat->envp);
	else if (len == 3 && !ft_strncmp(file, "env", 3))
		ms_env(arg, stat->envp);
	else if (len == 3 && !ft_strncmp(file, "pwd", 3))
		ms_pwd();
	else if (len == 4 && !ft_strncmp(file, "echo", 4))
		ms_echo(arg);
	else if (len == 4 && !ft_strncmp(file, "exit", 4))
		ms_exit(arg, stat->envp);
	else if (len == 5 && !ft_strncmp(file, "unset", 5))
		ms_unset(arg, stat->envp);
	else if (len == 6 && !ft_strncmp(file, "export", 6))
		ms_export(arg, stat->envp);
	else
		return (FALSE);
	return (TRUE);
}
