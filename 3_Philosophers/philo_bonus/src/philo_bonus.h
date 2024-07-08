/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:17:02 by daeha             #+#    #+#             */
/*   Updated: 2024/07/09 04:49:58 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

# define ARG_ERR	-1
# define OPTION_OFF -2

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int				name;
	size_t			birth_time;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				count_meal;
	int				current_meal;
	int				is_eating;
	int				*terminate;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*eat;
	sem_t			*dead;
}	t_philo;

typedef struct s_stat
{	
	sem_t			*forks;
	sem_t			*write;
	sem_t			*eat;
	sem_t			*dead;
	int				terminate;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_meal;
	t_philo			philo;
	pid_t			*pids;
}	t_stat;

//init_bonus.c
int		init(int argc, char **argv, t_stat *stat);

//procs_bonus.c
void	control_procs(t_stat *stat);

//procs_monitor_bonus.c 
void	*monitoring(void *arg);

//procs_philo_bonus.c
void	eat_think_sleep(t_stat *stat);

//utils_bonus.c
int		ft_atoi(const char *str);
size_t	ft_gettime(void);
int		ft_usleep(size_t ms);
void	ft_print_semaphore(char *msg, t_philo *philo);
void	free_resources(t_stat *stat);

#endif
