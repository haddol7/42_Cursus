/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:30 by daeha             #+#    #+#             */
/*   Updated: 2024/07/10 19:39:03 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitor_one_philo(t_stat *stat, int i);
static int	is_philo_starving(t_stat *stat, int i);
static void	*terminate(t_stat *stat, void *arg);

void	*monitoring(void *arg)
{
	t_stat	*stat;
	int		all_philo_eat;
	int		i;

	stat = (t_stat *)arg;
	while (TRUE)
	{
		i = -1;
		all_philo_eat = TRUE;
		while (++i < stat->num_philos)
		{	
			if (stat->philos[i].count_meal != OPTION_OFF)
			{
				pthread_mutex_lock(&stat->eat);
				if (stat->philos[i].current_meal < stat->philos[i].count_meal)
					all_philo_eat = FALSE;
				pthread_mutex_unlock(&stat->eat);
			}
			else
				all_philo_eat = FALSE;
			if (!all_philo_eat && monitor_one_philo(stat, i))
				return (arg);
		}
		if (all_philo_eat)
			return (terminate(stat, arg));
	}
	return (arg);
}

static int	monitor_one_philo(t_stat *stat, int i)
{
	if (is_philo_starving(stat, i))
	{	
		pthread_mutex_lock(&stat->dead);
		stat->terminate = TRUE;
		pthread_mutex_unlock(&stat->dead);
		pthread_mutex_lock(&stat->write);
		printf("%zu %d died\n", \
			ft_gettime() - stat->philos[i].birth_time, stat->philos[i].name);
		pthread_mutex_unlock(&stat->write);
		return (TRUE);
	}
	return (FALSE);
}

static int	is_philo_starving(t_stat *stat, int i)
{
	t_philo	philo;

	philo = stat->philos[i];
	pthread_mutex_lock(&stat->eat);
	if (ft_gettime() - philo.last_meal > philo.time_to_die)
	{
		pthread_mutex_unlock(&stat->eat);
		return (TRUE);
	}
	pthread_mutex_unlock(&stat->eat);
	return (FALSE);
}

static void	*terminate(t_stat *stat, void *arg)
{
	pthread_mutex_lock(&stat->dead);
	stat->terminate = TRUE;
	pthread_mutex_unlock(&stat->dead);
	return (arg);
}
