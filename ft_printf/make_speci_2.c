/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_speci_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:09:26 by daeha             #+#    #+#             */
/*   Updated: 2024/01/30 19:25:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*make_speci_d_i_getstr(long arg, int *len)
{
	char	*str;

	*len = 0;
	if (arg == 0)
	{
		(*len) = 1;
		return (ft_strdup("0", len));
	}
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
	str = (char *)malloc((*len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

int make_speci_d_i(t_spec *spec, t_flag flag, va_list *ap)
{
	int		len;
	char	*str;
	long	arg;

	arg = (long)va_arg(*ap, int);
	str = make_speci_d_i_getstr(arg, &len);
	if (str == NULL)
		return (ERROR);
	spec->size = len;
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
	spec->str = str;
	spec->type = 'd';
	return (make_field_d_i(spec, flag));
}

static char	*make_speci_u_getstr(long long arg, int *len)
{
	char	*str;

	*len = 0;
	if (arg == 0)
	{
		(*len) = 1;
		return (ft_strdup("0", len));
	}
	while (arg < 0)
	{
		arg /= 10;
		(*len)++;
	}
	str = (char *)malloc((*len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

int make_speci_u(t_spec *spec, t_flag flag, va_list *ap)
{
	int				len;
	char			*str;
	unsigned long	arg;

	arg = (long long)va_arg(*ap, unsigned int);
	str = make_speci_u_getstr(arg, &len);
	if (str == NULL)
		return (ERROR);
	spec->size = len;
	str[len--] = '\0';
	while (arg != 0 && len >= 0)
	{
		str[len--] = arg % 10 + '0';
		arg /= 10;
	}
	spec->str = str;
	spec->type = 'u';
	return (make_field_u(spec, flag));
}
int make_speci_per(t_spec *spec, t_flag flag)
{
	char	*str;

	str = ft_strdup("%", &spec->size);
	if (str == NULL)
		return (ERROR);
	spec->str = str;
	spec->type = '%';
	return (make_field_per(spec, flag));
}
