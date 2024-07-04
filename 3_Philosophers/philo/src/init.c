/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:40:48 by daeha             #+#    #+#             */
/*   Updated: 2024/07/04 20:28:36 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_args(int argc, char **argv, t_stat *stat);

int	init(int argc, char **argv, t_stat *stat)
{
	if(!validate_args(argc, argv, stat))
		return (0);
	return (1);
}

static int	validate_args(int argc, char **argv, t_stat *stat)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == ARG_ERR || (argc != 5 && argc != 6))
		{
			write(2, "Argument is not formatted.\n", 27);
			return (0);
		}
		i++;
	}
	stat->num_philos = ft_atoi(argv[1]);
	stat->time_to_eat = ft_atoi(argv[2]);
	stat->time_to_die = ft_atoi(argv[3]);
	stat->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		stat->num_to_eat = ft_atoi(argv[5]);
	else
		stat->num_to_eat = OPTION_OFF;
	return (1);
}
