/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:21:15 by daeha             #+#    #+#             */
/*   Updated: 2024/07/09 20:03:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	control_procs(t_stat *stat)
{
	int 	status;
	int		i;

	status = EXIT_SUCCESS;
	i = -1;
	while (++i < stat->num_philos)
	{
		stat->philo.name = i + 1;
		stat->pids[i] = fork();
		if (!stat->pids[i])
			proc_philos(stat);
	}
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
