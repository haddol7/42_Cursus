/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:30 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 17:57:00 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_philo_starving(t_stat *stat, size_t time_do_die);

void	*monitoring(void *arg)
{
	t_stat	*stat;
	size_t	time_to_die;

	stat = (t_stat *)arg;
	time_to_die = stat->time_to_die;
	while (TRUE)
	{
		if (is_philo_starving(stat, time_to_die))
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

static int	is_philo_starving(t_stat *stat, size_t time_to_die)
{
	t_philo	philo;

	philo = stat->philo;
	sem_wait(philo.unique_eat);
	if (ft_gettime() - philo.last_meal > time_to_die)
	{
		sem_post(philo.unique_eat);
		return (TRUE);
	}
	sem_post(philo.unique_eat);
	return (FALSE);
}
