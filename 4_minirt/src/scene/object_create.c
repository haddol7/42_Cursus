/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:27 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 03:23:45 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libft.h"

t_object *object(t_object_type type, void *element, t_color3 albedo, char *texture, void *mlx)
{
	t_object *new;

	if (!(new = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_object));
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	if (texture && ft_strcmp(texture, "CHECKER") == 0)
		new->is_checker = TRUE;
	else if (texture)
	{
		new->bump.img.id = mlx_xpm_file_to_image(mlx, "./brick_normal.xpm", &new->bump.width, &new->bump.height);
		new->bump.img.addr = mlx_get_data_addr(new->bump.img.id, &new->bump.img.bits_per_pixel, &new->bump.img.line_size, &new->bump.img.endian);
		
		new->texture.img.id = mlx_xpm_file_to_image(mlx, texture, &new->texture.width, &new->texture.height);
		if (new->texture.img.id == NULL)
		{
			write(STDERR_FILENO, "image file error\n", 18);
			//new->is_checker = TRUE;
		} 
		else
			new->texture.img.addr = mlx_get_data_addr(new->texture.img.id, &new->texture.img.bits_per_pixel, \
														&new->texture.img.line_size, &new->texture.img.endian);
	}
	return (new);
}

t_sphere *sphere(t_point3 center, double radius)
{
	t_sphere *sp;

	if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
    t_light *light;

    if(!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->origin = light_origin;
    light->light_color = light_color;
    light->bright_ratio = bright_ratio;
    return (light);
}
