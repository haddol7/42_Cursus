/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:21:51 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:44:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	result = ft_strdup(s);
	if (result == NULL)
		return (NULL);
	while (result[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}

// #include <stdio.h>

// static char	test(unsigned int i, char c)
// {
// 	if (i % 2 == 1)
// 		c = '!';
// 	return (c);
// }

// int	main(int argc, char **argv)
// {
// 	char	*str;

// 	str = ft_strmapi(argv[1], test);
// 	printf("%s\n", str);
// 	free(str);
// 	str = ft_strmapi(argv[2], NULL);
// 	printf("%s", str);
// 	str = ft_strmapi("", test);
// 	printf("%s", str);
// 	return (0);
// }
