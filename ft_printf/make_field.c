/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 16:41:47 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int make_field_c_p_per(t_field *field, t_flag flag)
{
	flag.zero = SPACE;
	if (!join_width(field, flag))
		return (ERROR);
	return (OK);
}

int make_field_s(t_field *field, t_flag flag)
{
	flag.zero = SPACE;
	if (field->size > flag.preci && flag.preci >= 0)
		field->size = flag.preci;
	if (!join_width(field, flag))
		return (ERROR);
	return (OK);
}

int make_field_u(t_field *field, t_flag flag)
{
	flag_priority(&flag);
	if (field->str[0] == '0' && flag.preci == 0)
	{
		field->str[0] = '\0';
		field->size = 0;
		flag.zero = SPACE;
	}
	if (!join_preci(field, flag.preci) || !join_width(field, flag))
		return (ERROR);
	return (OK);
}

int make_field_d_i(t_field *field, t_flag flag)
{
	flag_priority(&flag);
	if (field->str[0] == '0' && flag.preci == 0)
	{
		field->str[0] = '\0';
		field->size = 0;
	}
	if (!join_preci(field, flag.preci) || \
		!join_sign(field, flag.sign, flag.sign_p) || \
		!join_width(field, flag))
		return (ERROR);
	return (OK);
}

int	make_field_x_X(t_field *field, t_flag flag)
{
	char	is_reverse;
	
	is_reverse = 0;
	flag_priority(&flag);
	if (flag.alt == 1 && flag.zero == ZERO)
		is_reverse = 1;
	if (field->str[0] == '0' && flag.preci == 0)
	{
		field->str[0] = '\0';
		field->size = 0;
		flag.zero = SPACE;
	}
	if (!join_preci(field, flag.preci))
		return (error_free(field));
	if (is_reverse == 1)
	{
		flag.width -= 2;
		if (!join_width(field, flag) || !join_alt(field, flag.alt))
			return (error_free(field));
		return (OK);
	}
	if (!join_alt(field, flag.alt) || !join_width(field, flag))
			return (error_free(field));	
	return (OK);
}
