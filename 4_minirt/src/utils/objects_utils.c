/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:06 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 19:11:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	oadd(t_object **list, t_object *new)
{
	t_object	*cur;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}

t_object	*olast(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	terminate(void *data_addr)
{
	t_data	*data;

	data = (t_data *)data_addr;
	mlx_destroy_image(data->engine->mlx, data->engine->img->id);
	mlx_destroy_window(data->engine->mlx, data->engine->win);
	printf("\033[0;92mProgram closed!\n");
	exit(0);
}
