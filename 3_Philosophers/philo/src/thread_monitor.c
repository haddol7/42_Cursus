/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:30 by daeha             #+#    #+#             */
/*   Updated: 2024/07/09 00:41:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitor_one_philo(t_stat *stat, int i);
static int	is_philo_starving(t_stat *stat, int i);

void	*monitoring(void *arg)
{
	t_stat	*stat;
	int		loop;
	int		all_eat;
	int		i;

	loop = TRUE;
	stat = (t_stat *)arg;
	while (loop)
	{
		i = 0;
		all_eat = TRUE;
		while (i < stat->num_philos)
		{	
			pthread_mutex_lock(&stat->eat);
			if (stat->philos[i].count_meal == OPTION_OFF || stat->philos[i].current_meal < stat->philos[i].count_meal)
				all_eat = FALSE;
			pthread_mutex_unlock(&stat->eat);
			if (monitor_one_philo(stat, i))
			{
				loop = FALSE;
				break ;
			}
			i++;
		}
		if (all_eat)
		{
			pthread_mutex_lock(&stat->dead);
			stat->terminate = TRUE;
			pthread_mutex_unlock(&stat->dead);
			break ;
		}
	}
	return (arg);
}

static int	monitor_one_philo(t_stat *stat, int i)
{
	if (is_philo_starving(stat, i))
	{	
		pthread_mutex_lock(&stat->write);
		pthread_mutex_lock(&stat->dead);
		printf("%zu %d died\n", ft_gettime() - stat->philos[i].birth_time, stat->philos[i].name);
		stat->terminate = TRUE;
		pthread_mutex_unlock(&stat->write);
		pthread_mutex_unlock(&stat->dead);
		return (TRUE);
	}
	return (FALSE);
}

static int	is_philo_starving(t_stat *stat, int i)
{
	t_philo	philo;

	philo = stat->philos[i];
	pthread_mutex_lock(&stat->eat);
	if (philo.is_eating == FALSE && ft_gettime() - philo.last_meal >= philo.time_to_die)
	{
		pthread_mutex_unlock(&stat->eat);
		return (TRUE);
	}
	pthread_mutex_unlock(&stat->eat);
	return (FALSE);
}
