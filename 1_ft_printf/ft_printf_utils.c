/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 23:45:28 by daeha             #+#    #+#             */
/*   Updated: 2024/01/31 17:14:00 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	swap(char *ch1, char *ch2)
{
	char	temp;

	temp = *ch1;
	*ch1 = *ch2;
	*ch2 = temp;
}

int	error_free(t_field *field)
{
	if (field->str != NULL)
		free(field->str);
	field->str = NULL;
	field->size = 0;
	return (ERROR);
}

char	*ft_strdup(const char *str, int *size)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (str[len] != '\0')
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	while (i++ < len)
		res[i] = str[i];
	*size = len;
	return (res);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (src < dst && len != 0)
	{
		i = len;
		while (i-- != 0)
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i != len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
