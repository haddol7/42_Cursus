/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:03:55 by daeha             #+#    #+#             */
/*   Updated: 2024/08/20 15:01:55 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# define KEY_ESC	53
# define KEY_Q		12
# define KEY_W		13
# define KEY_E		14
# define KEY_R		15
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_C		8
# define KEY_Z 		6
# define KEY_P		35
# define KEY_I		34
# define KEY_LEFT	123
# define KEY_RIGHT	124

# define MOUSE_LEFT		1
# define MOUSE_RIGHT	2
# define MOUSE_MID		3
# define MOUSE_UP		4
# define MOUSE_DOWN		5

# define ERR_MLC		12
# define ERR_MLX		42

int	key_hook(int keycode, void *data_addr);
int	key_release_hook(int keycode, void *data_addr);
int	mouse_press_hook(int keycode, int x, int y, void *data_addr);
int	mouse_drag_hook(int x, int y, void *data_addr);
int	mouse_release_hook(int keycode, int x, int y, void *data_addr);

#endif
