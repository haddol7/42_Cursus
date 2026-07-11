/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:18:16 by daeha             #+#    #+#             */
/*   Updated: 2024/07/16 21:01:40 by daeha            ###   ########.fr       */
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

size_t	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_philo *philo)
{
	size_t	start;

	start = ft_gettime();
	while (ft_gettime() - start < ms)
	{
		if (is_philo_terminated(philo))
			break ;
		usleep(250);
	}
	return (0);
}

void	ft_print_mutex(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->write);
	if (is_philo_terminated(philo))
	{
		pthread_mutex_unlock(philo->write);
		return ;
	}
	printf("%zu %d %s\n", ft_gettime() - philo->birth_time, philo->name, msg);
	pthread_mutex_unlock(philo->write);
}

int	is_philo_terminated(t_philo *philo)
{	
	pthread_mutex_lock(philo->dead);
	if (*philo->terminate)
	{
		pthread_mutex_unlock(philo->dead);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->dead);
	return (FALSE);
}
