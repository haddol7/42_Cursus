/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:57:58 by daeha             #+#    #+#             */
/*   Updated: 2024/01/28 17:45:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	char	*spe;
	int		size;
	t_flag	flag;

	if (format[*i] == '\0')
		return (1);
	parse_flag(format, &flag, i);
	if (!make_speci(&spe, ap, format, i) || \
		!make_field(&str, spe, flag, size) || \
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
