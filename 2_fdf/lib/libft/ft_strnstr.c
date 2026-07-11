/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:17:02 by daeha             #+#    #+#             */
/*   Updated: 2023/11/18 20:21:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		is_found;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && len--)
	{
		if (needle[0] == *haystack)
		{
			i = 0;
			is_found = 1;
			while (needle[i] != '\0' && haystack[i] != '\0')
			{
				if (haystack[i] != needle[i] || i > len)
					is_found = 0;
				i++;
			}
			if (is_found && !(haystack[i] == 0 && needle[i] != 0))
				return ((char *)haystack);
		}
		haystack++;
	}
	return (0);
}
// #include <string.h>
// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	char *s1 = "abc";
// 	char *s2 = "abcdef";
// 	size_t max = 3;
// 	char *i1 = strnstr(s1, s2, max);
// 	char *i2 = ft_strnstr(s1, s2, max);
// 	printf("%s %s", i1, i2);
// 	return (0);
// }
