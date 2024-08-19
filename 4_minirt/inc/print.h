/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:58:01 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 18:58:13 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "stdio.h"
# include "structures.h"

void	draw_ray_chunk(t_scene *scene, t_mlx *engine);
void	draw_ray_orig(t_scene *scene, t_mlx *engine);
void	write_color(t_img *img, t_color3 pixel_color, int x, int y);

#endif
