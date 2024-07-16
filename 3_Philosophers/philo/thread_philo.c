/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:37 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 20:50:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine_even(t_philo *philo);
static void	routine_odd(t_philo *philo);

void	*eat_think_sleep(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
	if (~philo->name & 1)
	{
		usleep(200);
		routine_even(philo);
	}
	else
		routine_odd(philo);
	return (arg);
}

static void	routine_even(t_philo *philo)
{
	while (!is_philo_terminated(philo))
	{
		p_eat_even(philo);
		if (philo->current_meal == philo->count_meal)
			break ;
		p_sleep(philo);
		p_think(philo);
		usleep(200);
	}
}

static void	routine_odd(t_philo *philo)
{
	while (!is_philo_terminated(philo))
	{
		p_eat_odd(philo);
		if (philo->current_meal == philo->count_meal)
			break ;
		p_sleep(philo);
		p_think(philo);
		usleep(200);
	}
}

void	use_fork(t_fork *fork, t_philo *philo)
{
	while (TRUE)
	{	
		if (philo->is_all_philo == ODD && philo->current_meal && \
			ft_gettime() - philo->last_meal <= philo->time_to_eat * 2)
		{
			usleep(100);
			continue ;
		}
		pthread_mutex_lock(&fork->mutex);
		if (fork->status == NOT_USING)
		{
			fork->status = USING;
			pthread_mutex_unlock(&fork->mutex);
			ft_print_mutex("has taken a fork", philo);
			return ;
		}
		pthread_mutex_unlock(&fork->mutex);
		usleep(100);
	}
}

void	use_done_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->status = NOT_USING;
	pthread_mutex_unlock(&fork->mutex);
}
