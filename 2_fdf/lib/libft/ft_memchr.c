/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:51:08 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:23:53 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*uc_s;
	size_t			i;

	uc_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (uc_s[i] == (unsigned char)c)
			return ((void *)(uc_s + i));
		i++;
	}
	return (0);
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int main(int argc, char **argv)
// {
// 	char *s = malloc(sizeof(char) * 5);
// 	for (int i = 0; i < 5; i++)
// 		s[i] = 'a' + i;
// 	for (int i = 0; i < 5; i++)
// 	{
// 		printf("std : %s\n", memchr(s, 'a' + i, atoi(argv[1])));
// 		printf("ft  : %s\n\n", ft_memchr(s, 'a' + i, atoi(argv[1])));
// 	}
// 	return (0);
// }
