/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:57:58 by daeha             #+#    #+#             */
/*   Updated: 2024/01/27 14:04:50 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	while (1)
	{
		if (format[offset + i] == '\0' || format[offset + i] == '%')
		{
			if (!write_literally(format, i, &offset, &result) ||\
				!write_conversion(format, i, &offset, &result))
				return (-1);
			if (format[offset + i] == '\0')
				break ;
		}
		i++;
	}
	va_end(ap);
	return (result);
}
