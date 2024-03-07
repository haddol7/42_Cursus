/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:23:17 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:58:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}

// #include <stdio.h>

// void	test(unsigned int i, char *ch)
// {
// 	if (i % 2 == 0)
// 		*ch = '!';
// }

// int main(int argc, char **argv)
// {
// 	char	*s1;

// 	s1 = ft_strdup(argv[1]);
// 	ft_striteri(NULL, NULL);
// 	printf("%s", s1);
// 	free(s1);
// 	return (0);
// }
