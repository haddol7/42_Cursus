/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:32:09 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 21:32:22 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int g_status;

void	ms_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		g_status = EXIT_FAILURE;
		return ;
	}
	ft_putendl_fd(dir, STDIN_FILENO);
	free(dir);
	g_status = EXIT_SUCCESS;
}
