/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:52:14 by jungslee          #+#    #+#             */
/*   Updated: 2024/08/25 00:04:01 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	is_in_valid_normalize_range(double x, double y, double z)
{
	if (!(-1.0 <= x && x <= 1.0))
		return (0);
	if (!(-1.0 <= y && y <= 1.0))
		return (0);
	if (!(-1.0 <= z && z <= 1.0))
		return (0);
	return (1);
}

int	is_color_in_valid_range(double r, double g, double b)
{
	if (!(0.0 <= r && r <= 1.0))
		return (0);
	if (!(0.0 <= g && g <= 1.0))
		return (0);
	if (!(0.0 <= b && b <= 1.0))
		return (0);
	return (1);
}

int	is_valid_ratio_range(double ratio)
{
	if (!(0.0 <= ratio && ratio <= 1.0))
		return (0);
	return (1);
}

void	object_normal(t_object *object, char *str, t_mlx engine)
{
	char	*path;

	path = ft_strtrim(str, "\n");
	object->bump.img.id = mlx_xpm_file_to_image(engine.mlx, path, \
							&object->bump.width, &object->bump.height);
	if (object->bump.img.id == NULL)
	{
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, " <- Bump file error\n", 21);
	}
	else
		object->bump.img.addr = mlx_get_data_addr(object->bump.img.id, \
		&object->bump.img.bits_per_pixel, \
		&object->bump.img.line_size, &object->bump.img.endian);
	free(path);
}
