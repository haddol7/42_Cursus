/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:31:54 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 21:32:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int g_status;

void	ms_unset(char **arg, t_env *stat)
{
	if (arg != NULL || stat != NULL)
		printf("ms_unset func detected\n");

	g_status = EXIT_SUCCESS;
}
