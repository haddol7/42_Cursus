/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:18:16 by daeha             #+#    #+#             */
/*   Updated: 2024/07/15 18:18:24 by daeha            ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	char	*str;
	long	l_n;
	size_t	len;

	l_n = (long)n;
	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		exit(1);
	str[len--] = '\0';
	while (l_n != 0 && len >= 0)
	{
		str[len] = l_n % 10 + '0';
		l_n /= 10;
		len--;
	}
	return (str);
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
		usleep(250);
	return (0);
}

void	ft_print_semaphore(char *msg, t_philo *philo)
{	
	sem_wait(philo->write);
	printf("%zu %d %s\n", ft_gettime() - philo->birth_time, philo->name, msg);
	sem_post(philo->write);
}
