/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:58:07 by daeha             #+#    #+#             */
/*   Updated: 2024/01/28 22:19:21 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

#  define OK 1
#  define ERROR 0

typedef struct s_flag
{
	int	width;
	int	preci;
	int	alt;
	int	left;
	int	sign;
	int	sign_p;
	int	zero;
}	t_flag;

typedef struct s_specifier
{
	char	*str;
	char	type;
}	t_spec;

int		ft_printf(const char *format, ...);
void	parse_flag(const char *format, t_flag *flag, int *i);
int		make_speci(t_spec *spec, va_list *ap, char ch);
int 	make_field(char **str, t_spec spec, t_flag flag, int *size);
#endif
