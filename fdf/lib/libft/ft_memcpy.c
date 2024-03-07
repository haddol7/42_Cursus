/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:07:49 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:29:50 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int	main(int argc, char **argv)
// {
// 	char	dst[4];
// 	char	*src = NULL;

// 	dst[1] = '0';
// 	size_t n = (size_t)atoi(argv[1]);

// 	char *cpy_std = ft_memcpy(0, 0, 5);
// 	return (0);
// }
