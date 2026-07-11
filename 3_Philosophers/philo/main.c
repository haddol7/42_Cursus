/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:46:31 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 21:00:41 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_resources(t_stat *stat);

int	main(int argc, char **argv)
{
	t_stat	stat;

	if (!init(argc, argv, &stat))
		return (1);
	control_threads(&stat);
	free_resources(&stat);
	return (0);
}

static void	free_resources(t_stat *stat)
{
	int	i;

	pthread_mutex_destroy(&stat->dead);
	pthread_mutex_destroy(&stat->write);
	pthread_mutex_destroy(&stat->eat);
	pthread_mutex_destroy(&stat->start);
	i = 0;
	while (i < stat->num_philos)
	{
		memset(&stat->philos[i], 0, sizeof(t_philo));
		pthread_mutex_destroy(&stat->forks[i].mutex);
		i++;
	}
	free(stat->philos);
	free(stat->forks);
	memset(stat, 0, sizeof(t_stat));
}
