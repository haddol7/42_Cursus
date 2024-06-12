/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:40:58 by daeha             #+#    #+#             */
/*   Updated: 2024/06/12 17:43:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_bool	is_builtin(char **arg, t_stat *stat)
{
	char	*file;
	size_t	len;

	file = arg[0];
	len = ft_strlen(arg[0]);
	if (ft_strncmp(arg[0]))
}
