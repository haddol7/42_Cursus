/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:32:09 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 23:20:20 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

extern int	g_status;

void	ms_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		g_status = EXIT_FAILURE;
		return ;
	}
	ft_putendl_fd(dir, STDOUT_FILENO);
	free(dir);
	g_status = EXIT_SUCCESS;
}
