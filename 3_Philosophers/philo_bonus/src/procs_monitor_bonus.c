/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:30 by daeha             #+#    #+#             */
/*   Updated: 2024/07/11 20:25:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_starving_exit(t_stat *stat);
static int	is_philo_starving(t_stat *stat);

void	*monitoring(void *arg)
{
	t_stat	*stat;

	stat = (t_stat *)arg;
	while (TRUE)
	{
		if (stat->philo.count_meal != OPTION_OFF)
		{
			sem_wait(stat->philo.eat);
			if (stat->philo.current_meal >= stat->philo.count_meal)
			{
				sem_post(stat->philo.eat);
				return (arg);
			}
			sem_post(stat->philo.eat);
		}
		check_starving_exit(stat);
	}
	return (arg);
}

static void	check_starving_exit(t_stat *stat)
{
	if (is_philo_starving(stat))
	{	
		sem_wait(stat->write);
		printf("%zu %d died\n", \
				ft_gettime() - stat->philo.birth_time, stat->philo.name);
		exit(EXIT_FAILURE);
	}
}

static int	is_philo_starving(t_stat *stat)
{
	t_philo	philo;

	philo = stat->philo;
	sem_wait(stat->eat);
	if (ft_gettime() - philo.last_meal >= philo.time_to_die)
	{
		sem_post(stat->eat);
		return (TRUE);
	}
	sem_post(stat->eat);
	return (FALSE);
}
