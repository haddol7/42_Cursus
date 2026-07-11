/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:30 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 20:49:55 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitor_starvation(t_stat *stat, int i, size_t time_to_die);
static int	is_philo_starving(t_stat *stat, int i, size_t time_to_die);
static int	is_all_philos_full(t_stat *stat);

void	*monitoring(void *arg)
{
	t_stat	*stat;
	size_t	time_to_die;
	int		i;

	stat = (t_stat *)arg;
	time_to_die = stat->time_to_die;
	pthread_mutex_lock(&stat->start);
	pthread_mutex_unlock(&stat->start);
	while (TRUE)
	{
		i = 0;
		while (i < stat->num_philos)
		{	
			if (monitor_starvation(stat, i, time_to_die))
				return (arg);
			i++;
		}
	}
	return (arg);
}

static int	monitor_starvation(t_stat *stat, int i, size_t time_to_die)
{
	if (is_philo_starving(stat, i, time_to_die))
	{
		pthread_mutex_lock(&stat->dead);
		stat->terminate = TRUE;
		pthread_mutex_unlock(&stat->dead);
		if (is_all_philos_full(stat))
			return (TRUE);
		pthread_mutex_lock(&stat->write);
		printf("%zu %d died\n", \
			ft_gettime() - stat->philos[i].birth_time, stat->philos[i].name);
		pthread_mutex_unlock(&stat->write);
		return (TRUE);
	}
	return (FALSE);
}

static int	is_philo_starving(t_stat *stat, int i, size_t time_to_die)
{
	pthread_mutex_lock(&stat->eat);
	if (ft_gettime() - stat->philos[i].last_meal > time_to_die)
	{
		pthread_mutex_unlock(&stat->eat);
		return (TRUE);
	}
	pthread_mutex_unlock(&stat->eat);
	return (FALSE);
}

static int	is_all_philos_full(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->num_philos)
	{	
		pthread_mutex_lock(&stat->eat);
		if (stat->count_meal != stat->philos[i].current_meal)
		{
			pthread_mutex_unlock(&stat->eat);
			return (FALSE);
		}
		pthread_mutex_unlock(&stat->eat);
		i++;
	}
	return (TRUE);
}
