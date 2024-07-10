/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:17:02 by daeha             #+#    #+#             */
/*   Updated: 2024/07/10 21:21:11 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ARG_ERR	-1
# define OPTION_OFF -2

# define TRUE 1
# define FALSE 0

typedef struct s_stat
{
	int				terminate;
	int				num_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				count_meal;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat;
}	t_stat;

typedef struct s_philo
{
	pthread_t		thread;
	int				name;
	size_t			birth_time;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				count_meal;
	int				current_meal;
	int				*terminate;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eat;
}	t_philo;

//init.c
int		init(int argc, char **argv, t_stat *stat);

//thread.c
void	control_threads(t_stat *stat);

//thread_monitor.c
void	*monitoring(void *arg);

//thread_philo.c
void	*eat_think_sleep(void *arg);
int		is_philo_terminated(t_philo *philo);

//utils.c
int		ft_atoi(const char *str);
size_t	ft_gettime(void);
int		ft_usleep(size_t ms, t_philo *philo);
void	ft_print_mutex(char *msg, t_philo *philo);
void	free_resources(t_stat *stat);

#endif
