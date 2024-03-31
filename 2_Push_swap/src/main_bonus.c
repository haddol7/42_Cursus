/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/03/31 17:49:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

/*
sa	|	node_swap(&a);
sb 	|	node_swap(&b);
ss 	|	node_swap(&a) && node_swap(&b)
pa 	|	push(&a, pop(&b, TOP), TOP);
pb 	|	push(&b, pop(&a, TOP), TOP);
ra 	|	push(&a, pop(&a, TOP), BOT);
rb 	|	push(&b, pop(&b, TOP), BOT);
rr 	|	ra && rb
rra |	push(&a, pop(&a, BOT), TOP);
rrb |	push(&b, pop(&b, BOT), TOP);
rrr |	rra && rrb
*/

#include <stdio.h>
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

int	atoi_fit(const char *str)
{
	long	result;
	int		temp;
	int		sign;

	sign = 1;
	result = 0;
	str = move_to_num(str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		temp = (int)result;
		if (temp != result)
		{
			perror("error");
			return (-1);
		}
		str++;
	}
	return ((int)(sign * result));
}

int main(int argc, char **argv)
{
	printf("%d", atoi_fit(argv[1]));
}
