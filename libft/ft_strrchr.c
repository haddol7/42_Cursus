/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:33:41 by daeha             #+#    #+#             */
/*   Updated: 2023/11/18 19:50:06 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = 0;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			str = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (str);
}

// #include <string.h>
// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	printf("%s %s", strrchr(argv[1],*argv[2]), ft_strrchr(argv[1],*argv[2]));
// 	return (0);
// }
