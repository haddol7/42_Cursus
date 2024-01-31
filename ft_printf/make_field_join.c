/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_field_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:19:12 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 16:48:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_priority(t_flag *flag)
{
	if (flag->sign_p == TRUE)
		flag->sign = FALSE;
	if (flag->preci >= 0 || flag->left == TRUE)
		flag->zero = SPACE;
}

static void	join_width_2(char *str, t_field *field, t_flag flag, int space)
{
	int		to_swap;
	char	first;

	to_swap = FALSE;
	first = field->str[0];
	if ((first == '-' || first == '+' || first == ' ') && \
		flag.zero == ZERO)
		to_swap = TRUE;
	if (flag.left == TRUE)
	{
		ft_memmove(str, field->str, field->size);
		ft_memset(str + field->size, SPACE, space);
	}
	else
	{
		ft_memset(str, flag.zero, space);
		ft_memmove(str + space, field->str, field->size);
		if (to_swap)
			swap(str, str + space);
	}
}

int join_width(t_field *field, t_flag flag)
{
	char	*str;
	int		space;

	space = flag.width - field->size;
	if (space <= 0)
		return (OK);
	str = (char *)malloc(sizeof(char) * (flag.width + 1));
	if (str == NULL)
		return (error_free(field));
	str[flag.width] = '\0';
	join_width_2(str, field, flag, space);
	free(field->str);
	field->str = str;
	field->size = flag.width;
	return (OK);
}

int	join_preci(t_field *field, int preci)
{
	char	*str;
	int		space;
	int		is_minus;

	is_minus = 0;
	if (field->str[0] == '-')
	{
		is_minus = 1;
		preci++;
	}
	space = preci - field->size;
	if (space <= 0)
		return (OK);
	str = (char *)malloc(sizeof(char) * (preci + 1));
	if (str == NULL)
		return (error_free(field));
	str[preci] = '\0';
	ft_memset(str, '0', space);
	ft_memmove(str + space, field->str, field->size);
	if (is_minus)
		swap(str, str + space);
	free(field->str);
	field->str = str;
	field->size = preci;
	return (OK);
}

int	join_alt(t_field *field, int alt)
{
	char	*str;

	if (alt == 0)
		return (OK);
	str = (char *)malloc(sizeof(char) * field->size + 2);
	if (str == NULL)
		return (error_free(field));
	ft_memmove(str + 2, field->str, field->size);
	str[0] = '0';
	if (field->type == 'x')
		str[1] = 'x';
	else 
		str[1] = 'X';
	free(field->str);
	field->str = str;
	field->size += 2;
	return (OK);
}

int	join_sign(t_field *field, int sign, int sign_p)
{
	char	*str;
	char	ch;
	
	if (field->str[0] == '-' || (sign == 0 && sign_p == 0))
		return (OK);
	if (sign == 1)
		ch = ' ';
	else
		ch = '+';
	str = (char *)malloc(sizeof(char) * field->size + 2);
	if (str == NULL)
		return (error_free(field));
	str[0] = ch;
	str[field->size + 1] = '\0';
	ft_memmove(str + 1, field->str, field->size);
	free(field->str);
	field->str = str;
	field->size += 1;
	return (OK);
}
