/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:37 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 18:38:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_think(t_philo *philo);
static void	p_sleep(t_philo *philo);
static void	p_eat_odd(t_philo *philo);
static void	p_eat_even(t_philo *philo);

void	*eat_think_sleep(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (~philo->name & 1)
		usleep(200);
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
	while (!is_philo_terminated(philo))
	{
		if (~philo->name & 1)
			p_eat_odd(philo);
		else
			p_eat_even(philo);
		if (philo->current_meal == philo->count_meal)
			break ;
		p_sleep(philo);
		p_think(philo);
		usleep(200);
	}
	return (arg);
}

static void	p_think(t_philo *philo)
{	
	ft_print_mutex("is thinking", philo);
}

static void	p_sleep(t_philo *philo)
{
	ft_print_mutex("is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

static void	p_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print_mutex("has taken a fork", philo);
	if (philo->l_fork == philo->r_fork)
	{	
		ft_usleep(philo->time_to_die + 100, philo);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ft_print_mutex("has taken a fork", philo);
	ft_print_mutex("is eating", philo);
	pthread_mutex_lock(philo->eat);
	philo->last_meal = ft_gettime();
	philo->current_meal++;
	pthread_mutex_unlock(philo->eat);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

// ./philo 3 610 200 100 연산은 최대한 간단하게
// philo busy waiting
// bool	put_fork(t_fork *fork)
// {
// 	while (TRUE)
// 	{ 	
//		pthread_mutex_lock(fork.mutex);
// 		if (fork.is_used == FALSE)
// 		{
// 			fork.is_use = TRUE;
// 			pthread_mutex_unlock(fork.mutex);

// 			return (TRUE);
// 		}
// 		pthread_mutex_unlock(fork.mutex);
// 		usleep(100);
// 		if (info.philo_num == 1)
// 		{
// 			while (!is_dead(info.dead.data))
// 				usleep(100);
// 			return (FALSE);
// 		}
// 	}
// }

static void	p_eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print_mutex("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	ft_print_mutex("has taken a fork", philo);
	ft_print_mutex("is eating", philo);
	pthread_mutex_lock(philo->eat);
	philo->last_meal = ft_gettime();
	philo->current_meal++;
	pthread_mutex_unlock(philo->eat);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
