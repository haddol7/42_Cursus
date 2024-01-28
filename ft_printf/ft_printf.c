/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:57:58 by daeha             #+#    #+#             */
/*   Updated: 2024/01/28 21:03:26 by daeha            ###   ########.fr       */
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
	
	while (1)
	{
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
		(*i)++;
	}
	parse_width(format, flag, i);
}

int make_speci(t_spec *spec, va_list *ap, char ch)
{
	if (ch == 'c')
		make_speci_c(spec, ap);
	else if (ch == 's')
		make_speci_s(spec, ap);
	else if (ch == 'p')
		make_speci_p(spec, ap);
	else if (ch == 'd')
		make_speci_d(spec, ap);
	else if (ch == 'i')
		make_speci_i(spec, ap);
	else if (ch == 'x')
		make_speci_x(spec, ap);
	else if (ch == 'X')
		make_speci_X(spec, ap);
	else if (ch == 'u')
		make_speci_u(spec, ap);
	else if (ch == '%')
		make_speci_per(spec, ap);
}

int make_field(char **str, t_spec spec, t_flag flag, int *size)
{
	
}

int	write_literally(const char *format, int len, int *result)
{
	int	temp;

	temp = write(1, format, len);
	if (temp < 0)
		return (0);
	*result += temp;
	return (1);
}

int	write_conversion(const char *format, int *i, int *result, va_list *ap)
{
	char	*str;
	int		size;
	t_spec	spec;
	t_flag	flag;

	if (format[*i] == '\0')
		return (1);
	parse_flag(format, &flag, i);
	if (!make_speci(&spec, ap, format[(*i)++]) || \
		!make_field(&str, spec, flag, &size) || \
		!write_literally(str, size, *result))
		return (0);
	if (str != NULL)
		free(str);
	str = NULL;
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int		result;
	int		offset;
	int		i;
	va_list	ap;

	result = 0;
	offset = 0;
	i = 0;
	va_start(ap, format);
	while (format[offset] == '\0')
	{
		if (format[offset + i] == '\0' || format[offset + i] == '%')
		{
			if (!write_literally(format + offset, i, &result) || \
				!write_conversion(format + offset, &i, &result, &ap))
				return (-1);
			offset = i;
			i = 0;
		}
		i++;
	}
	va_end(ap);
	return (result);
}
