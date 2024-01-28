/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:18:27 by daeha             #+#    #+#             */
/*   Updated: 2024/01/28 21:18:36 by daeha            ###   ########.fr       */
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
	else if (ch == 'd')
		no_err = make_speci_d(spec, ap);
	else if (ch == 'i')
		no_err = make_speci_i(spec, ap);
	else if (ch == 'x')
		no_err = make_speci_x(spec, ap);
	else if (ch == 'X')
		no_err = make_speci_X(spec, ap);
	else if (ch == 'u')
		no_err = make_speci_u(spec, ap);
	else if (ch == '%')
		no_err = make_speci_per(spec, ap);
	return (no_err);
}

int make_field(char **str, t_spec spec, t_flag flag, int *size)
{
	
}
