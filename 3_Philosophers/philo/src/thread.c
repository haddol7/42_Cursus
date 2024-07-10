/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:21:15 by daeha             #+#    #+#             */
/*   Updated: 2024/07/10 23:50:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	control_threads(t_stat *stat)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	pthread_create(&monitor, NULL, monitoring, stat);
	while (++i < stat->num_philos)
	{
		pthread_create(&stat->philos[i].thread, NULL, \
		&eat_think_sleep, &stat->philos[i]);
		usleep(1);
	}
	i = -1;
	pthread_join(monitor, NULL);
	while (++i < stat->num_philos)
		pthread_join(stat->philos[i].thread, NULL);
}
