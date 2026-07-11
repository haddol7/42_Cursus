/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:12:21 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:34:40 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// int	main(int argc, char **argv)
// {
// 	char	*b;
// 	int		c;
// 	size_t	len;

// 	b = strdup(argv[1]);
// 	c = *(argv[2]);
// 	len = (size_t)atoi(argv[3]);

// 	printf("%s%s", (char *)(memset(b, c, len)), 
// 	(char *)(ft_memset(b, c, len)));
// 	return (0);
// }
