/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:30 by daeha             #+#    #+#             */
/*   Updated: 2024/07/10 20:36:39 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitor_one_philo_starvation(t_stat *stat, int i);
static int	is_philo_starving(t_stat *stat, int i);
static int	is_all_philos_full(t_stat *stat);

void	*monitoring(void *arg)
{
	t_stat	*stat;
	int		i;

	stat = (t_stat *)arg;
	while (TRUE)
	{
		i = 0;
		while (i < stat->num_philos)
		{	
			if (monitor_one_philo_starvation(stat, i))
				return (arg);
			i++;
		}
		if (stat->count_meal != OPTION_OFF && is_all_philos_full(stat))
			return (arg);
	}
	return (arg);
}

static int	monitor_one_philo_starvation(t_stat *stat, int i)
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
	size_t	last_meal;
	int		current_meal;

	pthread_mutex_lock(&stat->eat);
	last_meal = stat->philos[i].last_meal;
	current_meal = stat->philos[i].current_meal;
	pthread_mutex_unlock(&stat->eat);
	if (ft_gettime() - last_meal > stat->time_to_die)
	{
		if (current_meal == stat->count_meal)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static int	is_all_philos_full(t_stat *stat)
{
	int	i;
	int	current_eat;

	i = 0;
	while (i < stat->num_philos)
	{	
		pthread_mutex_lock(&stat->eat);
		current_eat = stat->philos[i].current_meal;
		pthread_mutex_unlock(&stat->eat);
		if (stat->count_meal > current_eat)
			return (FALSE);
		i++;
	}
	pthread_mutex_lock(&stat->dead);
	stat->terminate = TRUE;
	pthread_mutex_unlock(&stat->dead);
	return (TRUE);
}
