/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 01:35:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	swap(char *ch1, char *ch2)
{
	char temp;

	temp = *ch1;
	*ch1 = *ch2;
	*ch2 = temp;
}

int	join_width(t_spec *spec, int width, int left, char zero)
{
	char	*str;
	int		space;
	int		to_swap;

	to_swap = 0;
	space = width - spec->size;
	if (spec->str[0] == '-' || spec->str[0] == '+' || spec->str[0] == ' ')
		to_swap = 1;
	if (space <= 0)
		return (OK);
	str = (char *)malloc(sizeof(char) * (width + 1));
	if (str == NULL)
		return (error_free(spec));
	str[width] = '\0';
	if (left == 1)
	{
		ft_memmove(str, spec->str, spec->size);
		ft_memset(str + spec->size, ' ', space);
	}
	else
	{
		ft_memset(str, zero, space);
		ft_memmove(str + space, spec->str, spec->size);
		if (zero == '0' && to_swap)
			swap(&str[0], &str[space]);
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
	int		is_minus;

	is_minus = 0;
	if (spec->str[0] == '-')
	{
		is_minus = 1;
		preci++;
	}
	space = preci - spec->size;
	if (space <= 0)
		return (OK);
	str = (char *)malloc(sizeof(char) * (preci + 1));
	if (str == NULL)
		return (error_free(spec));
	str[preci] = '\0';
	ft_memset(str, '0', space);
	ft_memmove(str + space, spec->str, spec->size);
	if (is_minus)
	{
		str[0] = '-';
		str[space] = '0';
	}
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
	if (str == NULL)
		return (error_free(spec));
	ft_memmove(str + 2, spec->str, spec->size);
	str[0] = '0';
	if (spec->type == 'x')
		str[1] = 'x';
	else 
		str[1] = 'X';
	free(spec->str);
	spec->str = str;
	spec->size += 2;
	return (OK);
}

int	join_sign(t_spec *spec, int sign, int sign_p)
{
	char	*str;
	char	ch;
	
	if (spec->str[0] == '-' || (sign == 0 && sign_p == 0))
		return (OK);
	if (sign == 1)
		ch = ' ';
	else
		ch = '+';
	str = (char *)malloc(sizeof(char) * spec->size + 2);
	if (str == NULL)
		return (error_free(spec));
	str[0] = ch;
	str[spec->size + 1] = '\0';
	ft_memmove(str + 1, spec->str, spec->size);
	free(spec->str);
	spec->str = str;
	spec->size += 1;
	return (OK);
}

int make_field_c_p(t_spec *spec, t_flag flag)
{
	if (!join_width(spec, flag.width, flag.left, ' '))
		return (ERROR);
	return (OK);
}

int make_field_s(t_spec *spec, t_flag flag)
{
	if (spec->size > flag.preci && flag.preci != -1)
		spec->size = flag.preci;
	if (!join_width(spec, flag.width, flag.left, ' '))
		return (ERROR);
	return (OK);
}

int make_field_per(t_spec *spec, t_flag flag)
{
	if (!join_width(spec, flag.width, flag.left, ' '))
		return (ERROR);
	return (OK);
}

int make_field_u(t_spec *spec, t_flag flag)
{
	char	is_zero;

	if (flag.preci >= 0 || flag.left != 0)
		flag.zero = 0;
	if (flag.zero == 0)
		is_zero = ' ';
	else
		is_zero = '0';
	if (spec->str[0] == '0' && flag.preci == 0)
	{
		spec->str[0] = '\0';
		spec->size = 0;
		is_zero = ' ';
	}
	if (!join_preci(spec, flag.preci) || \
		!join_width(spec, flag.width, flag.left, is_zero))
		return (ERROR);
	return (OK);
}

int make_field_d_i(t_spec *spec, t_flag flag)
{
	char	is_zero;
	
	if (flag.sign_p == 1)
		flag.sign = 0;
	if (flag.preci >= 0 || flag.left != 0)
		flag.zero = 0;
	if (flag.zero == 0)
		is_zero = ' ';
	else
		is_zero = '0';
	if (spec->str[0] == '0' && flag.preci == 0)
	{
		spec->str[0] = '\0';
		spec->size = 0;
	}
	if (!join_preci(spec, flag.preci) || \
		!join_sign(spec, flag.sign, flag.sign_p) || \
		!join_width(spec, flag.width, flag.left, is_zero))
		return (ERROR);
	return (OK);
}

int	make_field_x_X(t_spec *spec, t_flag flag)
{
	char	is_zero;
	char	is_reverse;
	
	is_zero = '0';
	is_reverse = 0;
	if (flag.preci >= 0 || flag.left != 0)
		flag.zero = 0;
	if (flag.zero == 0)
		is_zero = ' ';
	if (flag.alt == 1 && is_zero == '0')
		is_reverse = 1;
	if (spec->str[0] == '0' && flag.preci == 0)
	{
		spec->str[0] = '\0';
		spec->size = 0;
		is_zero = ' ';
	}
	if (!join_preci(spec, flag.preci))
		return (error_free(spec));
	if (is_reverse == 1)
	{
		if (!join_width(spec, flag.width - 2, flag.left, is_zero) || \
			!join_alt(spec, flag.alt))
			return (error_free(spec));
	}
	else
	{
		if (!join_alt(spec, flag.alt) || \
			!join_width(spec, flag.width, flag.left, is_zero))
			return (error_free(spec));
	}
		
	return (OK);
}
