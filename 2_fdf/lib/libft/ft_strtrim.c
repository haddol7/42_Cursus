/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:53:56 by daeha             #+#    #+#             */
/*   Updated: 2023/11/18 18:59:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	start;
	size_t	end;
	size_t	i;

	if (*s1 == '\0')
		return (ft_strdup(""));
	else if (*set == '\0')
		return (ft_strdup(s1));
	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (start != end && ft_strchr(set, s1[start]) != 0)
		start++;
	while (i != end && ft_strchr(set, s1[end - i]) != 0)
		i++;
	if (start > end - i)
		return (ft_strdup(""));
	result = ft_substr(s1, (unsigned int)start, end - i - start + 1);
	return (result);
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	char	*str;

// 	str = ft_strtrim("abcdba", "acb");
// 	printf("%s", str);
// 	return (0);
// }
