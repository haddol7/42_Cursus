/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:48 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 21:32:43 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int g_status;

void	ms_exit(char **arg, t_env *stat)
{
	if (arg != NULL || stat != NULL)
		printf("ms_exit func detected\n");
	g_status = EXIT_SUCCESS;
}
