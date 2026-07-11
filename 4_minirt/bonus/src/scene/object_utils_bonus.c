/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:06:22 by jungslee          #+#    #+#             */
/*   Updated: 2024/09/09 20:22:48 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_bonus.h"
#include "libft.h"

t_object	*object_default(t_object_type type, void *element, t_color3 albedo)
{
	t_object	*new;

	new = (t_object *)ft_malloc(sizeof(t_object));
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	return (new);
}

t_object	*object_texture(t_object_type type, \
							void *element, char *texture, void *mlx)
{
	t_object	*new;

	new = (t_object *)ft_malloc(sizeof(t_object));
	new->type = type;
	new->element = element;
	new->next = NULL;
	if (texture && ft_strcmp(texture, "CHECKER") == 0)
		new->is_checker = TRUE;
	else if (texture)
	{
		new->texture.img.id = mlx_xpm_file_to_image(mlx, texture, \
							&new->texture.width, &new->texture.height);
		if (new->texture.img.id == NULL)
		{
			write(STDERR_FILENO, "IMAGE ", 7);
			write(STDERR_FILENO, texture, ft_strlen(texture));
			write(STDERR_FILENO, " invalid\n", 10);
			new->is_checker = TRUE;
		}
		else
			new->texture.img.addr = mlx_get_data_addr(new->texture.img.id, \
			&new->texture.img.bits_per_pixel, \
			&new->texture.img.line_size, &new->texture.img.endian);
	}
	return (new);
}
