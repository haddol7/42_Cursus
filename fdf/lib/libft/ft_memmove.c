/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:11:37 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:31:45 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == 0 && src == 0)
		return (0);
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
// #include <string.h>
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	char	array[10];
// 	memset(array, 0, sizeof(array));
// 	strcpy(array, "123456");
// 	printf("original : %s\n", array);
// 	ft_memmove(array + 1, array, atoi(argv[1]));
// 	printf("after memmove : %s\n", array);
// 	return (0);
// }
