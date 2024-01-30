/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/01/30 19:00:03 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	join_width(t_spec *spec, int width, int left, char zero)
{
	char	*str;
	int		space;

	space = width - spec->size;
	if (space < 0)
		return (OK);
	str = (char *)malloc(sizeof(char) * (width + 1));
	if (str == NULL)
		return (ERROR);
	str[width] == '\0';
	if (left == 1)
	{
		ft_memmove(str, spec->str, spec->size);
		ft_memmset(str + spec->size, ' ', space);
	}
	else
	{
		ft_memset(str, zero, space);
		ft_memmove(str + space, spec->str, spec->size);
	}
	free(spec->str);
	spec->str = str;
	spec->size = width;
	return (OK);
}

int	join_preci(t_spec *spec, int preci)
{
	char	*str;
	int		space;

	space = preci - spec->size;
	if (space < 0)
		return (OK);
	str = (char *)malloc(sizeof(char) * (preci + 1));
	if (str == NULL)
		return (ERROR);
	str[preci] = '\0';
	ft_memset(str, '0', space);
	ft_memmove(str + space, spec->str, spec->size);
	free(spec->str);
	spec->str = str;
	spec->size = preci;
	return (OK);
}

int	join_alt(t_spec *spec, int alt)
{
	char	*str;

	if (alt == 0)
		return (OK);
	str = (char *)malloc(sizeof(char) * spec->size + 2);
	ft_memmove(str + 2, spec->str, spec->size);
	str[0] = '0';
	if (spec->type = 'x')
		str[1] = 'x';
	else 
		str[1] = 'X';
	free(spec->str);
	spec->str = str;
	spec->size += 2;
}

int	join_sign(t_spec *spec, int sign, int sign_p)
{
	char	*str;
	char	sign;
	
	if (spec->str[0] != '-' || (sign == 0 && sign_p == 0))
		return (OK);
	if (sign == 1)
		sign = ' ';
	else
		sign = '+';
	str = (char *)malloc(sizeof(char) * spec->size + 2);
	if (str == NULL)
		return (ERROR);
	str[0] = sign;
	str[spec->size + 1] = '\0';
	ft_memmove(str + 1, spec->str, spec->size);
	free(spec->str);
	spec->str = str;
	spec->size += 1;
	return (OK);
}

int make_field_c_p(t_spec *spec, t_flag flag)
{
	if (!join_width(spec, flag.width, flag.left, 0))
		return (ERROR);
	return (OK);
}

int make_field_s(t_spec *spec, t_flag flag)
{
	if (spec->size > flag.preci)
		spec->size = flag.preci;
	if (!join_width(spec, flag.width, flag.left, 0))
		return (ERROR);
	return (OK);
}

int make_field_per(t_spec *spec, t_flag flag)
{
	if (!join_width(spec, flag.width, flag.left, flag.zero))
		return (ERROR);
	return (OK);
}

int make_field_u(t_spec *spec, t_flag flag)
{
	char	ch;

	if (flag.zero == 0)
		ch = ' ';
	else
		ch = '0';
	if (flag.preci != 0 || flag.left != 0)
		flag.zero = 0;
	if (!join_preci(spec, flag.preci) || \
		!join_width(spec, flag.width, flag.left, ch))
		return (ERROR);
	return (OK);
}

int	make_field_x_X(t_spec *spec, t_flag flag)
{
	char	is_zero;
	
	if (flag.zero == 0)
		is_zero = ' ';
	else
		is_zero = '0';
	if (flag.preci != 0 || flag.left != 0)
		flag.zero = 0;
	if (!join_preci(spec, flag.preci) || \
		!join_alt(spec, flag.alt) || \
		!join_width(spec, flag.width, flag.left, is_zero))
		return (ERROR);
	return (OK);
}

int make_field_d_i(t_spec *spec, t_flag flag)
{
	char	is_zero;
	
	if (flag.zero == 0)
		is_zero = ' ';
	else
		is_zero = '0';
	if (flag.sign_p == 1)
		flag.sign = 0;
	if (flag.preci != 0 || flag.left != 0)
		flag.zero = 0;
	if (!join_preci(spec, flag.preci) || \
		!join_sign(spec, flag.sign, flag.sign_p) || \
		!join_width(spec, flag.width, flag.left, is_zero))
		return (ERROR);
	return (OK);
}
