/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:34:43 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:43:48 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;

	if (*dst == '\0' && *src == '\0')
		return (0);
	i = 0;
	len_src = 0;
	while (src[len_src] != 0)
		len_src++;
	while (i + 1 < dstsize && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (len_src);
}

// #include <string.h>
// #include <stdio.h>

// int main(int argc, char **argv)
// {
// 	ft_strlcpy(0, 0, 0);
// 	return (0);
// }
