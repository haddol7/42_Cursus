/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:08:19 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 19:20:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *philo)
{	
	ft_print_mutex("is thinking", philo);
}

void	p_sleep(t_philo *philo)
{
	ft_print_mutex("is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

void	p_eat_odd(t_philo *philo)
{
	use_fork(philo->r_fork, philo);
	if (philo->l_fork == philo->r_fork)
	{	
		ft_usleep(philo->time_to_die + 100, philo);
		return ;
	}
	use_fork(philo->l_fork, philo);
	ft_print_mutex("is eating", philo);
	pthread_mutex_lock(philo->eat);
	philo->last_meal = ft_gettime();
	philo->current_meal++;
	pthread_mutex_unlock(philo->eat);
	ft_usleep(philo->time_to_eat, philo);
	use_done_fork(philo->l_fork);
	use_done_fork(philo->r_fork);
}

void	p_eat_even(t_philo *philo)
{
	use_fork(philo->l_fork, philo);
	use_fork(philo->r_fork, philo);
	ft_print_mutex("is eating", philo);
	pthread_mutex_lock(philo->eat);
	philo->last_meal = ft_gettime();
	philo->current_meal++;
	pthread_mutex_unlock(philo->eat);
	ft_usleep(philo->time_to_eat, philo);
	use_done_fork(philo->r_fork);
	use_done_fork(philo->l_fork);
}
