/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_speci_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:09:26 by daeha             #+#    #+#             */
/*   Updated: 2024/01/30 15:10:13 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*make_speci_d_i_get_str(long arg, int *len)
{
	char	*str;

	*len = 0;
	if (arg == 0)
	{
		(*len) == 1;
		return (ft_strdup("0"));
	}
	if (arg < 0)
	{
		(*len)++;
		arg *= -1;
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

int make_speci_d_i(t_spec *spec, va_list *ap)
{
	int		len;
	char	*str;
	long	arg;

	arg = (long)va_arg(*ap, int);
	str = make_speci_d_i_getstr(arg, &len);
	if (str == NULL)
		return (ERROR);
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
	return (OK);
}

static char	*make_speci_u_getstr(long long arg, int *len)
{
	char	*str;

	*len = 0;
	if (arg == 0)
	{
		(*len) == 1;
		return (ft_strdup("0"));
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

int make_speci_u(t_spec *spec, va_list *ap)
{
	int				len;
	char			*str;
	unsigned long	arg;

	arg = (long long)va_arg(*ap, unsigned int);
	str = make_speci_u_getstr(arg, &len);
	if (str == NULL)
		return (ERROR);
	str[len--] = '\0';
	while (arg != 0 && len >= 0)
	{
		str[len--] = arg % 10 + '0';
		arg /= 10;
	}
	spec->str = str;
	spec->type = 'd';
	return (OK);
}
int make_speci_per(t_spec *spec)
{
	char	*str;

	str = ft_strdup("%");
	if (str == NULL)
		return (ERROR);
	spec->str = str;
	spec->type = '%';
	return (OK);
}
