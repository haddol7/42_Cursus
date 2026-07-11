/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:17:02 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 20:50:20 by daeha            ###   ########.fr       */
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

# define USING 1
# define NOT_USING 0

# define EVEN 0
# define ODD 1

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				status;
}	t_fork;

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
	int				is_all_philo;
	t_fork			*r_fork;
	t_fork			*l_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*start;
}	t_philo;

typedef struct s_stat
{
	int				terminate;
	int				num_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				count_meal;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat;
	pthread_mutex_t	start;
}	t_stat;

//init.c
int		init(int argc, char **argv, t_stat *stat);

//thread.c
void	control_threads(t_stat *stat);

//thread_monitor.c
void	*monitoring(void *arg);

//thread_philo.c
void	*eat_think_sleep(void *arg);
void	use_fork(t_fork *fork, t_philo *philo);
void	use_done_fork(t_fork *fork);

//thread_philo_utils.c
void	p_think(t_philo *philo);
void	p_sleep(t_philo *philo);
void	p_eat_odd(t_philo *philo);
void	p_eat_even(t_philo *philo);

//utils.c
int		ft_atoi(const char *str);
size_t	ft_gettime(void);
int		ft_usleep(size_t ms, t_philo *philo);
void	ft_print_mutex(char *msg, t_philo *philo);
int		is_philo_terminated(t_philo *philo);

#endif
