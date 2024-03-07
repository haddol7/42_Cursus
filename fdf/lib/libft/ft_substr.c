/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:29:01 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:53:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s_sub;
	size_t	s_len;
	size_t	s_sub_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		s_sub_len = 0;
	else if (start + len > s_len)
		s_sub_len = s_len - start;
	else
		s_sub_len = len;
	s_sub = (char *)malloc((s_sub_len + 1) * sizeof(char));
	if (s_sub == NULL)
		return (NULL);
	if (s_sub_len == 0)
	{
		*s_sub = '\0';
		return (s_sub);
	}
	ft_strlcpy(s_sub, s + start, s_sub_len + 1);
	return (s_sub);
}

// #include <stdio.h>
// int	main()
// {
// 	char	*result;
// 	result = ft_substr(0, -1, 1);
// 	printf("%s", result);
// 	return (0);
// }
