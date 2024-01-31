/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 16:13:28 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int make_field_c_p_per(t_field *spec, t_flag flag)
{
	flag.zero = SPACE;
	if (!join_width(spec, flag))
		return (ERROR);
	return (OK);
}

int make_field_s(t_field *spec, t_flag flag)
{
	flag.zero = SPACE;
	if (spec->size > flag.preci && flag.preci >= 0)
		spec->size = flag.preci;
	if (!join_width(spec, flag))
		return (ERROR);
	return (OK);
}

int make_field_u(t_field *spec, t_flag flag)
{
	flag_priority(&flag);
	if (spec->str[0] == '0' && flag.preci == 0)
	{
		spec->str[0] = '\0';
		spec->size = 0;
		flag.zero = SPACE;
	}
	if (!join_preci(spec, flag.preci) || \
		!join_width(spec, flag))
		return (ERROR);
	return (OK);
}

int make_field_d_i(t_field *spec, t_flag flag)
{
	flag_priority(&flag);
	if (spec->str[0] == '0' && flag.preci == 0)
	{
		spec->str[0] = '\0';
		spec->size = 0;
	}
	if (!join_preci(spec, flag.preci) || \
		!join_sign(spec, flag.sign, flag.sign_p) || \
		!join_width(spec, flag))
		return (ERROR);
	return (OK);
}

int	make_field_x_X(t_field *spec, t_flag flag)
{
	char	is_reverse;
	
	is_reverse = 0;
	flag_priority(&flag);
	if (flag.alt == 1 && flag.zero == ZERO)
		is_reverse = 1;
	if (spec->str[0] == '0' && flag.preci == 0)
	{
		spec->str[0] = '\0';
		spec->size = 0;
		flag.zero = SPACE;
	}
	if (!join_preci(spec, flag.preci))
		return (error_free(spec));
	if (is_reverse == 1)
	{
		flag.width -= 2;
		if (!join_width(spec, flag) || \
			!join_alt(spec, flag.alt))
			return (error_free(spec));
		return (OK);
	}
	if (!join_alt(spec, flag.alt) || \
		!join_width(spec, flag))
			return (error_free(spec));	
	return (OK);
}
