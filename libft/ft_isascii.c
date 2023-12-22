/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:12:26 by daeha             #+#    #+#             */
/*   Updated: 2023/11/08 17:36:00 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 0177)
		return (1);
	return (0);
}
// #include <ctype.h>
// #include <stdlib.h>
// #include <stdio.h>
// int main(int argc, char **argv)
// {
//     int val = atoi(argv[1]);
//     printf("%d %d\n",isascii(val),ft_isascii(val));
//     return (0);
// }
