/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:26:55 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"
#include "expansion_bonus.h"
#include "execution_bonus.h"
#include "minishell_bonus.h"

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
