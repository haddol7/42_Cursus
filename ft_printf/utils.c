/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:45:28 by daeha             #+#    #+#             */
/*   Updated: 2024/01/28 23:50:50 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *str)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (str[len] != '\0')
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	while (i++ < len)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}
