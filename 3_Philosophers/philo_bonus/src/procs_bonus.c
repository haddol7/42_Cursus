/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:21:15 by daeha             #+#    #+#             */
/*   Updated: 2024/07/09 05:58:01 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	proc_philos(t_stat *stat);

void	control_procs(t_stat *stat)
{
	pid_t	pid;
	int 	status;
	int		i;

	i = -1;
	status = EXIT_SUCCESS;
	while (++i < stat->num_philos)
	{
		stat->philo.name = i + 1;
		pid = fork();
		if (!pid)
			proc_philos(stat);
		else
			stat->pids[i] = pid;
	}
	i = -1;
	while (++i < stat->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != EXIT_SUCCESS)
		{	
			i = -1;
			while (++i < stat->num_philos)
			{
				kill(stat->pids[i], SIGKILL);
			}
			break ;
		}
	}
}

//pthread join vs detach
static void	proc_philos(t_stat *stat)
{	
	pthread_t	monitor;

	pthread_create(&monitor, NULL, monitoring, stat);
	eat_think_sleep(stat);
	sem_close(stat->forks);
	sem_close(stat->write);
	sem_close(stat->eat);
	sem_close(stat->dead);
	exit(EXIT_SUCCESS);
}
