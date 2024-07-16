/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:21:15 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 16:33:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	wait_procs(t_stat *stat);

void	control_procs(t_stat *stat)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = &stat->philo;
	sem_wait(stat->start);
	while (++i < stat->num_philos)
	{
		philo->name = i + 1;
		philo->str_name = ft_itoa(philo->name);
		sem_unlink(philo->str_name);
		philo->unique_eat = sem_open(philo->str_name, O_CREAT, 0644, 1);
		if (philo->unique_eat == SEM_FAILED)
			exit(EXIT_FAILURE);
		philo->birth_time = ft_gettime();
		philo->last_meal = philo->birth_time;
		stat->pids[i] = fork();
		if (!stat->pids[i])
			proc_philos(stat);
		sem_close(philo->unique_eat);
		free(philo->str_name);
	}
	sem_post(stat->start);
	wait_procs(stat);
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
