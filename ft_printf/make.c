/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:18:27 by daeha             #+#    #+#             */
/*   Updated: 2024/01/30 15:13:44 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int make_speci(t_spec *spec, va_list *ap, char ch)
{
	int no_err;

	no_err = OK; 
	if (ch == 'c')
		no_err = make_speci_c(spec, ap);
	else if (ch == 's')
		no_err = make_speci_s(spec, ap);
	else if (ch == 'p')
		no_err = make_speci_p(spec, ap);
	else if (ch == 'd' || ch == 'i')
		no_err = make_speci_d_i(spec, ap);
	else if (ch == 'x' || ch == 'X')
		no_err = make_speci_x_X(spec, ap, ch);
	else if (ch == 'u')
		no_err = make_speci_u(spec, ap);
	else if (ch == '%')
		no_err = make_speci_per(spec, ap);
	return (no_err);
}

int make_field(char **str, t_spec spec, t_flag flag, int *size)
{
	int		no_err;
	char	type;

	no_err = OK;
	type = spec.type;
	if (type = 'c')
		no_err = make_field_c(str, spec, flag, size);
	else if (type = 's')
		no_err = make_field_s(str, spec, flag, size);
	else if (type = 'p')
		no_err = make_field_p(str, spec, flag, size);
	else if (type = 'd')
		no_err = make_field_d(str, spec, flag, size);
	else if (type = 'i')
		no_err = make_field_i(str, spec, flag, size);
	else if (type = 'x')
		no_err = make_field_x(str, spec, flag, size);
	else if (type = 'X')
		no_err = make_field_X(str, spec, flag, size);
	else if (type = 'u')
		no_err = make_field_u(str, spec, flag, size);
	else if (type = '%')
		no_err = make_field_per(str, spec, flag, size);
	return (no_err);
}
