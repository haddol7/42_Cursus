/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:30 by daeha             #+#    #+#             */
/*   Updated: 2024/07/09 05:59:22 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	is_philo_starving_exit(t_stat *stat);
static int	is_philo_starving(t_stat *stat);

void	*monitoring(void *arg)
{
	t_stat	*stat;

	stat = (t_stat *)arg;
	while (TRUE)
	{
		sem_wait(stat->eat);
		if (stat->philo.count_meal != -2 && stat->philo.current_meal >= stat->philo.count_meal)
		{
			sem_post(stat->eat);
			return (arg);
		}
		sem_post(stat->eat);
		is_philo_starving_exit(stat);
	}
	return (arg);
}

//TODO :  stat->terminate 안씀
// write semaphore 분리하기
static void	is_philo_starving_exit(t_stat *stat)
{
	if (is_philo_starving(stat))
	{	
		sem_wait(stat->write);
		printf("%zu %d died\n", ft_gettime() - stat->philo.birth_time, stat->philo.name);
		//dprintf(2, "123\n");
		exit(EXIT_FAILURE);
		//sem_post(stat->write);
	}
}

static int	is_philo_starving(t_stat *stat)
{
	t_philo	philo;

	philo = stat->philo;
	sem_wait(stat->eat);
	if (philo.is_eating == FALSE && ft_gettime() - philo.last_meal >= philo.time_to_die)
	{
		sem_post(stat->eat);
		return (TRUE);
	}
	sem_post(stat->eat);
	return (FALSE);
}
