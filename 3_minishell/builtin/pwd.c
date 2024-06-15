/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:32:09 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 18:49:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		exit(EXIT_FAILURE);
	ft_putendl_fd(dir, STDIN_FILENO);
	free(dir);
	exit(EXIT_SUCCESS);
}
