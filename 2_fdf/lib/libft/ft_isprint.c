/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:21:37 by daeha             #+#    #+#             */
/*   Updated: 2023/11/08 17:36:12 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 040 && c <= 0176)
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// #include <stdlib.h>
// int	main(int argc, char **argv)
// {
// 	int val = atoi(argv[1]);
// 	printf("%d %d\n", isprint(val), ft_isprint(val));
// 	return (0);
// }
