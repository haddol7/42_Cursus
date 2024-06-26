/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:26:55 by daeha             #+#    #+#             */
/*   Updated: 2024/06/26 15:01:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expansion.h"
#include "execution.h"
#include "minishell.h"

int	error_cd_home(char *keyword)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(keyword, STDERR_FILENO);
	ft_putendl_fd(" not set", STDERR_FILENO);
	set_status(EXIT_FAILURE);
	return (0);
}

int	error_cd_enoent(char *file, char *target, t_bool target_malloc)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (file)
		ft_putstr_fd(file, STDERR_FILENO);
	else
		ft_putstr_fd(target, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(2), STDERR_FILENO);
	set_status(EXIT_FAILURE);
	if (target_malloc)
		free(target);
	return (0);
}
