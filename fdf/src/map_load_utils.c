/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:31:32 by daeha             #+#    #+#             */
/*   Updated: 2024/03/24 18:47:22 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(t_map *map)
{
	map->key = KEY_P;
	ft_memset(&map->translate, 0, sizeof(t_point));
	ft_memset(&map->angular, 0, sizeof(t_point));
	ft_memset(&map->mouse, 0, sizeof(t_mouse));
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
	*color = COLOR_NONE;
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
		return (COLOR_NONE);
	return (color);
}

void	set_default_color(int *z_color, int z)
{
	double	color[3];

	if (z > 0)
	{
		color[0] = (get_red(MOUNTAIN) - get_red(GROUND)) / Z_MAX_VAL;
		color[1] = (get_green(MOUNTAIN) - get_green(GROUND)) / Z_MAX_VAL;
		color[2] = (get_blue(MOUNTAIN) - get_blue(GROUND)) / Z_MAX_VAL;
		*z_color = ((int)(get_red(GROUND) + z * color[0]) << 16 | \
					(int)(get_green(GROUND) + z * color[1]) << 8 | \
					(int)(get_blue(GROUND) + z * color[2]));
	}
	else
	{
		color[0] = (get_red(GROUND) - get_red(OCEAN)) / Z_MIN_VAL * -1;
		color[1] = (get_green(GROUND) - get_green(OCEAN)) / Z_MIN_VAL * -1;
		color[2] = (get_blue(GROUND) - get_blue(OCEAN)) / Z_MIN_VAL * -1;
		z -= Z_MIN_VAL;
		*z_color = ((int)(get_red(OCEAN) + z * color[0]) << 16 | \
					(int)(get_green(OCEAN) + z * color[1]) << 8 | \
					(int)(get_blue(OCEAN) + z * color[2]));
	}
}

void	set_default_scale(t_map *map)
{
	if (map->col > map->row)
		map->scale = WINDOW_X_SIZE / (double)map->col;
	else
		map->scale = WINDOW_Y_SIZE / (double)map->row;
	if (map->scale < 0.1)
		map->scale = 0.1;
}
