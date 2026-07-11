/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:57:58 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 17:10:49 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_literally(const char *format, int len, int *res)
{
	int	temp;

	temp = write(1, format, len);
	if (temp < 0)
		return (ERROR);
	*res += temp;
	return (OK);
}

static int	write_field(const char *format, int *i, int *res, va_list *ap)
{
	t_field	field;
	t_flag	flag;

	if (format[*i] == '\0')
		return (OK);
	parse_flag(format, &flag, i);
	if (!make_conversion(&field, flag, ap, format[(*i)++]) || \
		!write_literally(field.str, field.size, res))
		return (ERROR);
	if (field.str != NULL)
		free(field.str);
	field.str = NULL;
	return (OK);
}

int	ft_printf(const char *format, ...)
{
	int		res;
	int		offset;
	int		i;
	va_list	ap;

	res = 0;
	offset = 0;
	i = 0;
	va_start(ap, format);
	while (format[offset] != '\0')
	{
		if (format[offset + i] == '\0' || format[offset + i] == '%')
		{
			if (!write_literally(format + offset, i, &res) || \
				!write_field(format + offset, &i, &res, &ap))
				return (-1);
			offset += i;
			i = -1;
		}
		i++;
	}
	va_end(ap);
	return (res);
}
