/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:31:32 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 15:49:03 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(t_map *map)
{
	map->translate.x = 0;
	map->translate.y = 0;
	map->translate.z = 0;
	map->angular.x = 0;
	map->angular.y = 0;
	map->angular.z = 0;
}

int	check_map_value(char **s, int *color)
{
	int				sign;
	long			res;
	int				i;

	i = 0;
	res = 0;
	sign = 1;
	if (**s == '-' || **s == ' ')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	while (ft_isdigit(**s))
	{
		res *= 10;
		res += (**s) - '0';
		(*s)++;
	}
	*color = 0xffffff;
	if (!ft_strncmp(*s, ",0x", 3) || !ft_strncmp(*s, ",0X", 3))
		*color = check_map_color(s);
	else if (!fdf_isspace(**s))
		fdf_error(ERR_M_VAL);
	return (res * sign);
}

int	check_map_color(char **s)
{
	size_t	i;
	int		color;

	color = 0x0;
	*s += 3;
	while (ft_isdigit(**s) || \
	(**s >= 'A' && **s <= 'F') || (**s >= 'a' && **s <= 'f'))
	{
		i = 0;
		if (**s >= 'a' && **s <= 'f')
			i = 10 + **s - 'a';
		else if (**s >= 'A' && **s <= 'F')
			i = 10 + **s - 'A';
		else
			i = **s - '0';
		color *= 16;
		color += i;
		(*s)++;
	}
	if (!fdf_isspace(**s))
		fdf_error(ERR_M_VAL);
	if (color == 0x0)
		return (0xffffff);
	return (color);
}
