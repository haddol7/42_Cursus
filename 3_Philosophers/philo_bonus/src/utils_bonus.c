/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:18:16 by daeha             #+#    #+#             */
/*   Updated: 2024/07/09 04:45:18 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = ft_gettime();
	while (ft_gettime() - start < ms)
		usleep(500);
	return (0);
}

void	ft_print_semaphore(char *msg, t_philo *philo)
{	
	sem_wait(philo->write);
	printf("%zu %d %s\n", ft_gettime() - philo->birth_time, philo->name, msg);
	sem_post(philo->write);
}

void	free_resources(t_stat *stat)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("eat");
	sem_unlink("dead");
	free(stat->pids);
	memset(&stat->philo, 0, sizeof(t_philo));
	memset(stat, 0, sizeof(t_stat));
}
