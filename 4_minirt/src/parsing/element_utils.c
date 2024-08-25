/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:50:57 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/25 00:03:54 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
}

int	count_split_words(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

t_point3	check_coordinate(char *coor)
{
	double	x;
	double	y;
	double	z;
	char	**split;

	split = ft_split(coor, ',');
	if (count_split_words(split) != 3)
		error_exit("not a complete coordinate\n");
	x = ft_atof(split[0]);
	y = ft_atof(split[1]);
	z = ft_atof(split[2]);
	free_split(split);
	return (point3(x, y, z));
}

t_color3	check_color(char *color)
{
	double	r;
	double	g;
	double	b;
	char	**split;

	split = ft_split(color, ',');
	if (count_split_words(split) != 3)
		error_exit("not complete rgb\n");
	r = ft_atof(split[0]) / 255;
	g = ft_atof(split[1]) / 255;
	b = ft_atof(split[2]) / 255;
	if (is_color_in_valid_range(r, g, b) == 0)
		error_exit("not valid RGB range\n");
	free_split(split);
	return (color3(r, g, b));
}

t_vec3	check_normalize_vector(char *coor)
{
	double	x;
	double	y;
	double	z;
	char	**split;

	split = ft_split(coor, ',');
	if (count_split_words(split) != 3)
		error_exit("not a complete vector\n");
	x = ft_atof(split[0]);
	y = ft_atof(split[1]);
	z = ft_atof(split[2]);
	if (is_in_valid_normalize_range(x, y, z) == 0)
		error_exit("not_valid_normalize_vector\n");
	free_split(split);
	return (vec3(x, y, z));
}
