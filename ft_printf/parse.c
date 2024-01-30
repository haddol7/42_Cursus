/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:16:47 by daeha             #+#    #+#             */
/*   Updated: 2024/01/30 19:37:52 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_precison(const char *format, t_flag *flag, int *i)
{
	char	cur;
	int		preci;

	preci = 0;
	while (1)
	{
		cur = format[*i];
		if (cur >= '0' && cur <= '9')
			preci = preci * 10 + (cur - '0');
		else
			break;
		(*i)++;
	}
	flag->preci = preci;
}
void	parse_width(const char *format, t_flag *flag, int *i)
{
	char	cur;
	int		width;

	width = 0;
	while (1)
	{
		cur = format[*i];
		if (cur >= '0' && cur <= '9')
			width = width * 10 + (cur - '0');
		else
			break;
		(*i)++;
	}
	flag->width = width;
	if (cur == '.')
		parse_precison(format, flag, i);
}

void	parse_flag(const char *format, t_flag *flag, int *i)
{
	char	cur;
	int		init_i;

	init_i = -1;
	while (++init_i != sizeof(*flag))
		((unsigned char *)flag)[init_i] = 0;
	while (1)
	{
		(*i)++;
		cur = format[*i];
		if (cur == '#')
			flag->alt = 1;
		else if (cur == '-')
			flag->left = 1;
		else if (cur == '+')
			flag->sign_p = 1;
		else if (cur == ' ')
			flag->sign = 1;
		else if (cur == '0')
			flag->zero = 1;
		else
			break;
	}
	parse_width(format, flag, i);
}
