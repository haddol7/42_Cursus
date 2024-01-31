/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_speci.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:36:33 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 17:17:50 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*make_speci_x_p_getstr(unsigned long long arg, int *len, char type)
{
	char	*str;

	*len = 0;
	if (arg == 0)
	{
		if (type == 'p')
			return (ft_strdup("0x0", len));
		else
			return (ft_strdup("0", len));
	}
	while (arg != 0)
	{
		arg /= 16;
		(*len)++;
	}
	if (type == 'p')
		*len += 2;
	str = (char *)malloc(sizeof(char) * (*len + 1));
	if (str == NULL)
		return (NULL);
	return (str);
}

int	make_speci_c(t_field *field, t_flag flag, va_list *ap)
{
	char	*str;
	char	arg;

	arg = va_arg(*ap, int);
	str = (char *)malloc(sizeof(char) * 2);
	if (str == NULL)
		return (ERROR);
	str[0] = arg;
	str[1] = '\0';
	field->str = str;
	field->type = 'c';
	field->size = 1;
	return (make_field_c_p_per(field, flag));
}

int	make_speci_s(t_field *field, t_flag flag, va_list *ap)
{
	char	*str;
	char	*arg;

	arg = va_arg(*ap, char *);
	if (arg == NULL)
		str = ft_strdup("(null)", &field->size);
	else
		str = ft_strdup(arg, &field->size);
	if (str == NULL)
		return (ERROR);
	field->str = str;
	field->type = 's';
	return (make_field_s(field, flag));
}

int	make_speci_p(t_field *field, t_flag flag, va_list *ap)
{
	char				*str;
	unsigned long long	arg;
	int					len;
	const char			*hex;

	hex = "0123456789abcdef";
	arg = (unsigned long long)va_arg(*ap, void *);
	str = make_speci_x_p_getstr(arg, &len, 'p');
	if (str == NULL)
		return (ERROR);
	field->size = len;
	str[0] = '0';
	str[1] = 'x';
	str[len--] = '\0';
	while (arg != 0 && len >= 0)
	{
		str[len--] = hex[arg % 16];
		arg /= 16;
	}
	field->str = str;
	field->type = 'p';
	return (make_field_c_p_per(field, flag));
}

int	make_speci_x(t_field *field, t_flag *flag, va_list *ap, char type)
{
	char				*str;
	unsigned long long	arg;
	int					len;
	const char			*hex;

	if (type == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	arg = (unsigned long long)va_arg(*ap, unsigned int);
	if (arg == 0)
		flag->alt = 0;
	str = make_speci_x_p_getstr(arg, &len, type);
	if (str == NULL)
		return (ERROR);
	field->size = len;
	str[len--] = '\0';
	while (arg != 0 && len >= 0)
	{
		str[len--] = hex[arg % 16];
		arg /= 16;
	}
	field->str = str;
	field->type = type;
	return (make_field_x(field, *flag));
}
