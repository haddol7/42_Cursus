/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:18:16 by daeha             #+#    #+#             */
/*   Updated: 2024/07/04 20:01:44 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*move_to_num(const char *str, int *sign);

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		printf("%zu\n", get_time() - start);
		usleep(800);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	str = move_to_num(str, &sign);
	if (sign == -1)
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		if (result < 0)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return ((int)(sign * result));
}

static const char	*move_to_num(const char *str, int *sign)
{
	while (*str != 0 && \
	(*str == '\t' || *str == '\n' || *str == ' ' || \
	*str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-')
	{
		*sign = -1;
		return (++str);
	}
	else if (*str == '+')
		return (++str);
	return (str);
}
