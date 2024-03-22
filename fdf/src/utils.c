/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:26:24 by daeha             #+#    #+#             */
/*   Updated: 2024/03/22 20:46:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

int	terminate(void *data_addr)
{
	t_client	*data;

	data = (t_client *)data_addr;
	mlx_destroy_image(data->mlx, data->img.id);
	mlx_destroy_window(data->mlx, data->win);
	free(data->map.point);
	free(data->map.copy);
	ft_printf("\033[0;92mProgram closed!\n");
	exit(0);
}

void	fdf_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_point(t_proj *first, t_proj *last)
{
	fdf_swap(&first->x_proj, &last->x_proj);
	fdf_swap(&first->y_proj, &last->y_proj);
	fdf_swap(&first->color, &last->color);
}

int	fdf_isspace(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\0')
		return (TRUE);
	return (FALSE);
}
