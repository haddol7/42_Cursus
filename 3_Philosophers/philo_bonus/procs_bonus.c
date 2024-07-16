/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:21:15 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 17:14:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	write_philo_info(t_stat *stat, int i);
static void	free_all_sems_exit(t_stat *stat, int i, int mode);
static void	wait_procs(t_stat *stat);

void	control_procs(t_stat *stat)
{
	int	i;

	i = -1;
	sem_wait(stat->start);
	while (++i < stat->num_philos)
	{
		write_philo_info(stat, i);
		stat->pids[i] = fork();
		if (!stat->pids[i])
			proc_philos(stat);
		else if (stat->pids[i] == -1)
			free_all_sems_exit(stat, i, ERR_FORK);
		sem_close(stat->philo.unique_eat);
		free(stat->philo.str_name);
	}
	sem_post(stat->start);
	wait_procs(stat);
}

static void	write_philo_info(t_stat *stat, int i)
{
	t_philo	*philo;

	philo = &stat->philo;
	philo->name = i + 1;
	philo->str_name = ft_itoa(philo->name);
	sem_unlink(philo->str_name);
	philo->unique_eat = sem_open(philo->str_name, O_CREAT, 0644, 1);
	if (philo->unique_eat == SEM_FAILED)
		free_all_sems_exit(stat, i, ERR_SEM);
	philo->birth_time = ft_gettime();
	philo->last_meal = philo->birth_time;
}

static void	wait_procs(t_stat *stat)
{
	int		status;
	int		i;

	status = EXIT_SUCCESS;
	i = -1;
	while (++i < stat->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != EXIT_SUCCESS)
		{	
			i = -1;
			while (++i < stat->num_philos)
				kill(stat->pids[i], SIGKILL);
			break ;
		}
	}
}

static void	free_all_sems_exit(t_stat *stat, int i, int mode)
{
	char	*str;

	sem_close(stat->start);
	sem_close(stat->forks);
	sem_close(stat->write);
	sem_unlink("start");
	sem_unlink("forks");
	sem_unlink("write");
	if (mode == ERR_FORK)
	{
		str = ft_itoa(i + 1);
		sem_unlink(str);
		free(str);
	}
	while (--i > 0)
	{
		kill(stat->pids[i], SIGKILL);
		str = ft_itoa(i + 1);
		sem_unlink(str);
		free(str);
	}
	free(stat->pids);
	exit(EXIT_FAILURE);
}
