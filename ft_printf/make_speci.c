/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_speci.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:36:33 by daeha             #+#    #+#             */
/*   Updated: 2024/01/29 12:06:43 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int make_speci_c(t_spec *spec, va_list *ap)
{
	char	*str;
	char	arg;

	arg = va_arg(*ap, int);
	str = (char *)malloc(sizeof(char) * 2);
	if (str == NULL)
		return (ERROR);
	str[0] = arg;
	str[1] = '\0';
	spec->str = str;
	spec->type = 'c';
	return (OK);
}

int make_speci_s(t_spec *spec, va_list *ap)
{
	char	*str;
	char	*arg;

	arg = va_arg(*ap, char *);
	str = ft_strdup(aㅂrg);
	if (str == NULL)
		return (ERROR);
	spec->str = str;
	spec->type = 's';
	return (OK);
}

int make_speci_p(t_spec *spec, va_list *ap)
{
	char				*str;
	const char			*hex;
	unsigned long long	arg;

	hex = "0123456789abcdef";
	arg = (unsigned long long)va_arg(*ap, void *);
	
}

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

static char	*make_speci_xX_getstr(long long arg, int *len)
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
		arg /= 16;
		(*len)++;
	}
	str = (char *)malloc((*len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

int make_speci_x(t_spec *spec, va_list *ap)
{
	int			len;
	char		*str;
	const char	*hex;
	long long	arg;

	hex = "0123456789abcdef";
	arg = (long long)va_arg(*ap, unsigned int);
	str = make_speci_xX_get_str(arg, &len);
	if (str == NULL)
		return (ERROR);
	str[len--] = '\0';
	while (arg != 0 && len >= 0)
	{
		str[len--] = hex[arg % 16];
		arg / 16;
	}
	spec->str = str;
	spec->type = 'd';
	return (OK);
}

int make_speci_X(t_spec *spec, va_list *ap)
{
	int			len;
	char		*str;
	const char	*hex;
	long long	arg;

	hex = "0123456789ABCDEF";
	arg = (long long)va_arg(*ap, unsigned int);
	str = make_speci_xX_get_str(arg, &len);
	if (str == NULL)
		return (ERROR);
	str[len--] = '\0';
	while (arg != 0 && len >= 0)
	{
		str[len--] = hex[arg % 16];
		arg / 16;
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

