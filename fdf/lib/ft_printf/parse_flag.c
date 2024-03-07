/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:16:47 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 17:18:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_precison(const char *format, t_flag *flag, int *i)
{
	char	cur;
	int		preci;

	preci = 0;
	while (1)
	{
		cur = format[++(*i)];
		if (cur >= '0' && cur <= '9')
			preci = preci * 10 + (cur - '0');
		else
			break ;
	}
	flag->preci = preci;
}

static void	parse_width(const char *format, t_flag *flag, int *i)
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
			break ;
		(*i)++;
	}
	flag->width = width;
	if (cur == '.')
		parse_precison(format, flag, i);
}

void	parse_flag(const char *format, t_flag *flag, int *i)
{
	int		init_i;

	init_i = -1;
	while (++init_i != sizeof(*flag))
		((unsigned char *)flag)[init_i] = FALSE;
	flag->preci = -1;
	flag->zero = SPACE;
	while (1)
	{
		(*i)++;
		if (format[*i] == '#')
			flag->alt = TRUE;
		else if (format[*i] == '-')
			flag->left = TRUE;
		else if (format[*i] == '+')
			flag->sign_p = TRUE;
		else if (format[*i] == ' ')
			flag->sign = TRUE;
		else if (format[*i] == '0')
			flag->zero = ZERO;
		else
			break ;
	}
	parse_width(format, flag, i);
}

void	flag_priority(t_flag *flag)
{
	if (flag->sign_p == TRUE)
		flag->sign = FALSE;
	if (flag->preci >= 0 || flag->left == TRUE)
		flag->zero = SPACE;
}
