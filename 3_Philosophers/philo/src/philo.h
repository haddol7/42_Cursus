/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:17:02 by daeha             #+#    #+#             */
/*   Updated: 2024/07/04 21:36:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define ARG_ERR	-1
# define OPTION_OFF -2

# define TRUE 1
# define FALSE 0

typedef struct	s_philo
{
	pthread_t		thread;
	int				name;
	size_t			birth_time;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				*is_dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eat;
} t_philo;

typedef struct s_stat
{
	int				is_dead;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	t_philo 		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
} t_stat;

//utils.c
size_t	get_time(void);
int		ft_usleep(size_t ms);
int		ft_atoi(const char *str);
void	free_resource(t_stat *stat);

int		init(int argc, char **argv, t_stat *stat);

#endif
