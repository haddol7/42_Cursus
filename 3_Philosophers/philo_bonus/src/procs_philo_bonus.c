/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:40:37 by daeha             #+#    #+#             */
/*   Updated: 2024/07/09 05:17:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	p_think(t_philo *philo);
static void	p_sleep(t_philo *philo);
static void	p_eat(t_philo *philo, int num_philos);

void	eat_think_sleep(t_stat *stat)
{
	t_philo	*philo;

	philo = &stat->philo;
	if (philo->name % 2 == 0)
		ft_usleep(1);
	while (philo->count_meal == -2 || philo->current_meal < philo->count_meal)
	{
		p_eat(philo, stat->num_philos);
		p_sleep(philo);
		p_think(philo);
	}
}

static void	p_think(t_philo *philo)
{	
	ft_print_semaphore("is thinking", philo);
}

static void	p_sleep(t_philo *philo)
{
	ft_print_semaphore("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

static void	p_eat(t_philo *philo, int num_philos)
{
	sem_wait(philo->forks);
	ft_print_semaphore("has taken a fork", philo);
	if (num_philos == 1)
	{	
		ft_usleep(philo->time_to_die);
		sem_post(philo->forks);
		return ;
	}
	sem_wait(philo->forks);
	ft_print_semaphore("has taken a fork", philo);
	ft_print_semaphore("is eating", philo);
	sem_wait(philo->eat);
	philo->is_eating = FALSE;
	philo->last_meal = ft_gettime();
	sem_post(philo->eat);
	ft_usleep(philo->time_to_eat);
	sem_wait(philo->eat);
	philo->is_eating = FALSE;
	philo->current_meal++;
	sem_post(philo->eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}
