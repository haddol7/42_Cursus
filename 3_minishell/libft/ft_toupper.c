/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:39:38 by daeha             #+#    #+#             */
/*   Updated: 2023/11/08 17:37:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
// #include <ctype.h>
// #include <stdio.h>
// int main(int argc, char **argv)
// {
//     printf("%c %c \n",toupper(*argv[1]),ft_toupper(*argv[1]));
//     return (0);
// }
