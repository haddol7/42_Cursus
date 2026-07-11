/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:46:42 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:26:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;

	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*uc_s1 != *uc_s2)
			return (*uc_s1 - *uc_s2);
		uc_s1++;
		uc_s2++;
	}
	return (0);
}
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// int main(int argc, char **argv)
// {
// 	int		s1[5] = {1,2,3,4,5};
// 	int		s2[5] = {1,256,3,4,5};
// 	size_t	n = (size_t)atoi(argv[1]);

// 	printf("%d\n", memcmp(0, 0, n));
// 	printf("%d", ft_memcmp(0, 0, n));
// }
