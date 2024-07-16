/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:30 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 16:46:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_philo_starving(t_stat *stat);

void	*monitoring(void *arg)
{
	t_stat	*stat;

	stat = (t_stat *)arg;
	while (TRUE)
	{
		if (is_philo_starving(stat))
		{
			sem_wait(stat->write);
			printf("%zu %d died\n", \
					ft_gettime() - stat->philo.birth_time, stat->philo.name);
			sem_close(stat->forks);
			sem_close(stat->philo.unique_eat);
			sem_unlink(stat->philo.str_name);
			free(stat->philo.str_name);
			free(stat->pids);
			exit(EXIT_FAILURE);
		}
		usleep(500);
	}
	return (arg);
}

static int	is_philo_starving(t_stat *stat)
{
	t_philo	philo;

	philo = stat->philo;
	sem_wait(philo.unique_eat);
	if (ft_gettime() - philo.last_meal >= philo.time_to_die)
	{
		sem_post(philo.unique_eat);
		return (TRUE);
	}
	sem_post(philo.unique_eat);
	return (FALSE);
}
