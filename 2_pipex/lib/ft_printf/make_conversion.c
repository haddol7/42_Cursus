/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:18:27 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 22:37:00 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	make_conversion(t_field *field, t_flag flag, va_list *ap, char speci)
{
	int	no_err;

	no_err = OK;
	field->str = NULL;
	field->size = 0;
	if (speci == 'c')
		no_err = make_speci_c(field, flag, ap);
	else if (speci == 's')
		no_err = make_speci_s(field, flag, ap);
	else if (speci == 'p')
		no_err = make_speci_p(field, flag, ap);
	else if (speci == 'd' || speci == 'i')
		no_err = make_speci_d_i(field, flag, ap, speci);
	else if (speci == 'x' || speci == 'X')
		no_err = make_speci_x(field, &flag, ap, speci);
	else if (speci == 'u')
		no_err = make_speci_u(field, flag, ap);
	else if (speci == '%')
		no_err = make_speci_per(field, flag);
	return (no_err);
}
