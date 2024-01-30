/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:58:07 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 01:09:40 by daeha            ###   ########.fr       */
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
	int		size;
}	t_spec;

int		ft_printf(const char *format, ...);
void	parse_flag(const char *format, t_flag *flag, int *i);
int		make_conversion(t_spec *spec, t_flag flag, va_list *ap, char ch);
int		make_speci_c(t_spec *spec, t_flag flag, va_list *ap);
int 	make_speci_s(t_spec *spec, t_flag flag, va_list *ap);
int 	make_speci_p(t_spec *spec, t_flag flag, va_list *ap);
int 	make_speci_x_X(t_spec *spec, t_flag *flag, va_list *ap, char type);
int		make_speci_d_i(t_spec *spec, t_flag flag, va_list *ap);
int		make_speci_u(t_spec *spec, t_flag flag, va_list *ap);
int		make_speci_per(t_spec *spec, t_flag flag);
int		join_width(t_spec *spec, int width, int left, char zero);
int		join_preci(t_spec *spec, int preci);
int		join_alt(t_spec *spec, int alt);
int		join_sign(t_spec *spec, int sign, int sign_p);
int		make_field_c_p(t_spec *spec, t_flag flag);
int		make_field_s(t_spec *spec, t_flag flag);
int		make_field_per(t_spec *spec, t_flag flag);
int		make_field_u(t_spec *spec, t_flag flag);
int		make_field_x_X(t_spec *spec, t_flag flag);
int		make_field_d_i(t_spec *spec, t_flag flag);
int		error_free(t_spec *spec);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strdup(const char *str, int *size);
void	*ft_memset(void *b, int c, size_t len);

#endif
