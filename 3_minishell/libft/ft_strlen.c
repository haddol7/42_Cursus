/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:42:58 by daeha             #+#    #+#             */
/*   Updated: 2024/06/08 04:45:44 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s != NULL && s[cnt] != '\0')
		cnt++;
	return (cnt);
}

// #include <string.h>
// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	const char	*s = 0;
// 	printf("%lu", strlen(s));
// 	return (0);
// }
