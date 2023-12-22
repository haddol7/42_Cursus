/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:06:33 by daeha             #+#    #+#             */
/*   Updated: 2023/11/22 15:46:49 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	if (dst == NULL && dstsize == 0)
		return (0);
	i = 0;
	len_dst = 0;
	len_src = 0;
	while (dst[len_dst] != 0)
		len_dst++;
	while (src[len_src] != 0)
		len_src++;
	while (i + len_dst + 1 < dstsize && src[i] != '\0')
	{
		dst[i + len_dst] = src[i];
		i++;
	}
	dst[i + len_dst] = '\0';
	if (len_dst < dstsize)
		return (len_src + len_dst);
	return (len_src + dstsize);
}
// #include <string.h>
// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	char	dst[30];
// 	char	src[10];
// 	size_t	dstsize;
// 	strcpy(dst, "123456789");
// 	strcpy(src, "abc");
// 	ft_strlcat(0, src, 0);
// 	printf("%s", dst);
// 	return (0);
// }
