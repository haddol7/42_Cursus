/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:32:09 by daeha             #+#    #+#             */
/*   Updated: 2024/06/24 23:57:59 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

void	ms_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		set_status(EXIT_FAILURE);
		return ;
	}
	ft_putendl_fd(dir, STDOUT_FILENO);
	free(dir);
	set_status(EXIT_SUCCESS);
}
