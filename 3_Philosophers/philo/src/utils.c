/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:18:16 by daeha             #+#    #+#             */
/*   Updated: 2024/07/08 18:43:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	result;

	result = 0;
	while (*str != 0 && (*str == '\t' || *str == '\n' || *str == ' ' || \
	*str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		if (result < 0)
			return (-1);
		str++;
	}
	if (*str != '\0' || (int)(result) != result)
		return (-1);
	return ((int)(result));
}

void	ft_print_mutex(char *msg, t_philo *philo)
{	
	//pthread_mutex_lock(philo->write);
	if (mutex_is_terminate(philo))
		return ;
	printf("%zu %d %s\n", ft_gettime() - philo->birth_time, philo->name, msg);
	//pthread_mutex_unlock(philo->write);
}

size_t	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = ft_gettime();
	while (ft_gettime() - start < ms)
		usleep(200);
	return (0);
}

void	free_resources(t_stat *stat)
{
	int	i;
	
	pthread_mutex_destroy(&stat->dead);
	pthread_mutex_destroy(&stat->write);
	pthread_mutex_destroy(&stat->eat);
	i = 0;
	while (i < stat->num_philos)
	{	
		memset(&stat->philos[i], 0, sizeof(t_philo));
		pthread_mutex_destroy(&stat->forks[i]);
		i++;
	}
	free(stat->philos);
	free(stat->forks);
	memset(stat, 0, sizeof(t_stat));
}
