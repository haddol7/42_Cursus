/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:58:01 by daeha             #+#    #+#             */
/*   Updated: 2024/09/09 20:42:00 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_BONUS_H
# define PRINT_BONUS_H

# include "structures_bonus.h"

# define CHUNK_DIV 100

void	draw_ray_chunk(t_scene *scene, t_mlx *engine);
void	draw_ray_orig(t_scene *scene, t_mlx *engine);
void	write_color(t_img *img, t_color3 pixel_color, int x, int y);

#endif
