/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:32:23 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 21:30:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

void	ms_cd(char **arg, t_env *stat)
{
	if (arg != NULL || stat != NULL)
		printf("ms_cd func detected\n");
}
