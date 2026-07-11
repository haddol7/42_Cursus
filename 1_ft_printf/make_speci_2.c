/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_speci_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:09:26 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 17:17:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*make_speci_d_i_getstr(long long arg, int *len)
{
	char	*str;

	*len = 0;
	if (arg == 0)
		return (ft_strdup("0", len));
	if (arg < 0)
	{
		(*len)++;
		arg *= -1;
	}
	while (arg != 0)
	{
		arg /= 10;
		(*len)++;
	}
	str = (char *)malloc(sizeof(char) +(*len + 1));
	if (str == NULL)
		return (NULL);
	return (str);
}

static char	*make_speci_u_getstr(unsigned long long arg, int *len)
{
	char	*str;

	*len = 0;
	if (arg == 0)
	{
		(*len) = 1;
		return (ft_strdup("0", len));
	}
	while (arg != 0)
	{
		arg /= 10;
		(*len)++;
	}
	str = (char *)malloc((*len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

int	make_speci_d_i(t_field *field, t_flag flag, va_list *ap, char type)
{
	char		*str;
	long long	arg;
	int			len;

	arg = (long long)va_arg(*ap, int);
	str = make_speci_d_i_getstr(arg, &len);
	if (str == NULL)
		return (ERROR);
	field->size = len;
	if (arg < 0)
	{
		arg *= -1;
		*str = '-';
	}
	str[len--] = '\0';
	while (arg != 0 && len >= 0)
	{
		str[len--] = arg % 10 + '0';
		arg /= 10;
	}
	field->str = str;
	field->type = type;
	return (make_field_d_i(field, flag));
}

int	make_speci_u(t_field *field, t_flag flag, va_list *ap)
{
	char				*str;
	unsigned long long	arg;
	int					len;

	arg = (unsigned long long)va_arg(*ap, unsigned int);
	str = make_speci_u_getstr(arg, &len);
	if (str == NULL)
		return (ERROR);
	field->size = len;
	str[len--] = '\0';
	while (arg != 0 && len >= 0)
	{
		str[len--] = arg % 10 + '0';
		arg /= 10;
	}
	field->str = str;
	field->type = 'u';
	return (make_field_u(field, flag));
}

int	make_speci_per(t_field *field, t_flag flag)
{
	char	*str;

	str = ft_strdup("%", &field->size);
	if (str == NULL)
		return (ERROR);
	field->str = str;
	field->type = '%';
	return (make_field_c_p_per(field, flag));
}
