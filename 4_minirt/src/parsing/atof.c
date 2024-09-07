/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:57 by daeha             #+#    #+#             */
/*   Updated: 2024/09/07 17:10:45 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	init_var(t_num *info, double *result, int *i)
{
	info->dot_flag = 0;
	info->mult = 1.0;
	info->sign = 1.0;
	*result = 0.0;
	*i = 0;
}

static void	is_neg(char *num, t_num *info, int *i)
{
	if (num[0] == '-')
	{
		info->sign = -1.0;
		(*i)++;
	}
}

static void	add_num(double *res, char *num, int i, t_num *info)
{
	double	result;

	result = *res;
	if (num[i] == '.')
		info->dot_flag = 1;
	else if (info->dot_flag == 0)
	{
		result *= 10.0;
		result += num[i] - '0';
	}
	else
	{
		result += (num[i] - '0') * pow(0.1, info->mult++);
		if (info->mult > 10)
			error_exit("add_num\n");
	}
	*res = result;
}

double	ft_atof(char *num)
{
	double	result;
	t_num	info;
	int		i;

	init_var(&info, &result, &i);
	is_neg(num, &info, &i);
	while (!(num[i] == '\0' || num[i] == '\n'))
	{
		if (!(ft_isdigit(num[i]) || num[i] == '.'))
			error_exit("ft_atof : not a digit\n");
		add_num(&result, num, i, &info);
		if (result > INT_MAX || result < INT_MIN)
			error_exit("ft_atof : too big\n");
		i++;
	}
	return (result * info.sign);
}
