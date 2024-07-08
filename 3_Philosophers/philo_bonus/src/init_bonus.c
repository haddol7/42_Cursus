/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:40:48 by daeha             #+#    #+#             */
/*   Updated: 2024/07/09 05:06:02 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	validate_args(int argc, char **argv, t_stat *stat);
static void	init_semaphore(t_stat *stat);
static void	init_philo(t_stat *stat);

int	init(int argc, char **argv, t_stat *stat)
{
	if (validate_args(argc, argv, stat))
		return (0);
	init_semaphore(stat);
	init_philo(stat);
	return (1);
}

static int	validate_args(int argc, char **argv, t_stat *stat)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (write(2, "Argument is not invalid.\n", 26));
	i = 0;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) == ARG_ERR || (i == 1 && !ft_atoi(argv[1])))
			return (write(2, "Argument is not formatted.\n", 27));
	}
	stat->terminate = FALSE;
	stat->num_philos = ft_atoi(argv[1]);
	stat->time_to_die = ft_atoi(argv[2]);
	stat->time_to_eat = ft_atoi(argv[3]);
	stat->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		stat->count_meal = ft_atoi(argv[5]);
	else
		stat->count_meal = OPTION_OFF;
	stat->pids = malloc(sizeof(pid_t) * stat->num_philos);
	if (stat->pids == NULL)
	{
		write(2, "Malloc error\n", 14);
		exit(EXIT_FAILURE);
	}
	return (0);
}

static void	init_semaphore(t_stat *stat)
{
	stat->forks = sem_open("forks", O_CREAT, 0644, stat->num_philos);
	stat->write = sem_open("write", O_CREAT, 0644, 1);
	stat->eat = sem_open("eat", O_CREAT, 0644, 1);
	stat->dead = sem_open("dead", O_CREAT, 0644, 1);
}

static void	init_philo(t_stat *stat)
{	
	stat->philo.name = 0;
	stat->philo.birth_time = ft_gettime();
	stat->philo.last_meal = ft_gettime();
	stat->philo.time_to_die = stat->time_to_die;
	stat->philo.time_to_eat = stat->time_to_eat;
	stat->philo.time_to_sleep = stat->time_to_sleep;
	stat->philo.count_meal = stat->count_meal;
	stat->philo.current_meal = 0;
	stat->philo.is_eating = FALSE;
	stat->philo.forks = stat->forks;
	stat->philo.write = stat->write;
	stat->philo.eat = stat->eat;
	stat->philo.dead = stat->dead;
}
