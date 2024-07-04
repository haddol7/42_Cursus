/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:40:48 by daeha             #+#    #+#             */
/*   Updated: 2024/07/04 21:37:20 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_args(int argc, char **argv, t_stat *stat);
static int	alloc_fork_and_philo(t_stat *stat);
static void	init_mutex(t_stat *stat);
static void	init_philo(t_stat *stat);

int	init(int argc, char **argv, t_stat *stat)
{
	if (validate_args(argc, argv, stat))
		return (0);
	if (alloc_fork_and_philo(stat))
		return (0);
	init_mutex(stat);
	init_philo(stat);
	return (1);
}

static void	init_mutex(t_stat *stat)
{
	int	i;

	pthread_mutex_init(&stat->dead, NULL);
	pthread_mutex_init(&stat->write, NULL);
	pthread_mutex_init(&stat->eat, NULL);
	i = 0;
	while (i < stat->num_philos)
	{	
		pthread_mutex_init(&stat->forks[i], NULL);
		i++;
	}
}

static int	alloc_fork_and_philo(t_stat *stat)
{
	stat->philos = malloc(sizeof(t_philo) * stat->num_philos);
	stat->forks = malloc(sizeof(pthread_mutex_t) * stat->num_philos);
	if (!stat->philos || !stat->forks)
	{
		write(2, "Malloc error occured\n", 22);
		if (stat->philos)
			free(stat->philos);
		if (stat->forks)
			free(stat->forks);
		return (1);
	}
	return (0);
}

static int	validate_args(int argc, char **argv, t_stat *stat)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (write(2, "Argument is not enough.\n", 25));
	i = 0;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) == ARG_ERR)
			return (write(2, "Argument is not formatted.\n", 27));
	}
	stat->is_dead = FALSE;
	stat->num_philos = ft_atoi(argv[1]);
	stat->time_to_eat = ft_atoi(argv[2]);
	stat->time_to_die = ft_atoi(argv[3]);
	stat->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		stat->num_to_eat = ft_atoi(argv[5]);
	else
		stat->num_to_eat = OPTION_OFF;
	return (0);
}

static void	init_philo(t_stat *stat)
{
	int		i;
	t_philo *philo;

	i = 0;
	while (i < stat->num_philos)
	{	
		philo = &stat->philos[i];
		philo->thread = NULL;
		philo->name = i + 1;
		philo->birth_time = get_time();
		philo->last_meal = get_time();
		philo->time_to_die = stat->time_to_die;
		philo->time_to_eat = stat->time_to_eat;
		philo->time_to_sleep = stat->time_to_sleep;
		philo->is_dead = FALSE;
		philo->r_fork = &stat->forks[i];
		philo->l_fork = &stat->forks[(i + 1) % stat->num_philos];
		philo->write = &stat->write;
		philo->dead = &stat->dead;
		philo->eat = &stat->eat;
		i++;
	}
}
