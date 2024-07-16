/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:46:31 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 15:47:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_resources(t_stat *stat);

int	main(int argc, char **argv)
{
	t_stat	stat;

	if (!init(argc, argv, &stat))
		return (1);
	control_procs(&stat);
	free_resources(&stat);
	return (0);
}

static void	free_resources(t_stat *stat)
{
	sem_close(stat->start);
	sem_close(stat->forks);
	sem_close(stat->write);
	sem_unlink("start");
	sem_unlink("forks");
	sem_unlink("write");
	free(stat->pids);
	memset(&stat->philo, 0, sizeof(t_philo));
	memset(stat, 0, sizeof(t_stat));
}
