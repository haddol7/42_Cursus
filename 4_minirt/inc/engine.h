/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:03:55 by daeha             #+#    #+#             */
/*   Updated: 2024/08/31 23:56:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "structures.h"

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_ZERO 29
# define KEY_BRACE_R 30
# define KEY_O 31
# define KEY_U 32
# define KEY_BRACE_L 33
# define KEY_I 34
# define KEY_P 35
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_SEMI 41
# define KEY_N 45
# define KEY_M 46
# define KEY_TAB 48
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC	53

# define MOUSE_LEFT		1
# define MOUSE_RIGHT	2
# define MOUSE_MID		3
# define MOUSE_UP		4
# define MOUSE_DOWN		5

# define ERR_MLC		12
# define ERR_MLX		42

int		key_hook(int keycode, void *data_addr);
int		mouse_press_hook(int keycode, int x, int y, void *data_addr);
int		mouse_drag_hook(int x, int y, void *data_addr);
int		mouse_release_hook(int keycode, int x, int y, void *data_addr);

void	object_translation(int keycode, t_vec3 *center, t_data *data);
void	object_rotation(int keycode, t_vec3 *normal);

void	handle_sphere(int keycode, t_data *data);
void	handle_plane(int keycode, t_data *data);
void	handle_cylinder(int keycode, t_data *data);
void	handle_cone(int keycode, t_data *data);
void	handle_light(int keycode, t_data *data);
void	handle_camera(int keycode, t_data *data);

#endif
