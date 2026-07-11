/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:18:41 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 16:19:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	str = move_to_num(str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		if (result < 0 && sign == 1)
			return (-1);
		else if (result < 0 && sign == -1)
			return (0);
		str++;
	}
	return ((int)(sign * result));
}

// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	printf("std : %d\n ft : %d", atoi(argv[1]), ft_atoi(argv[1]));
// }
