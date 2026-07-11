/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:09:58 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:55:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	my_get_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	l_n;
	size_t	len;

	if (n == 0)
		return (ft_strdup("0"));
	l_n = (long)n;
	len = my_get_len(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (l_n < 0)
	{
		l_n *= -1;
		*str = '-';
	}
	str[len--] = '\0';
	while (l_n != 0 && len >= 0)
	{
		str[len] = l_n % 10 + '0';
		l_n /= 10;
		len--;
	}
	return (str);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	char	*str;
// 	str = ft_itoa(ft_atoi(argv[1]));
// 	printf("%s", str);
// 	return (0);
// }
