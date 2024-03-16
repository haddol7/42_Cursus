/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:26:24 by daeha             #+#    #+#             */
/*   Updated: 2024/03/15 20:35:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include "fdf.h"

//when mlx library is used the errno is set by 3
void fdf_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	fdf_error(char *msg)
{
	if (errno == 3 || errno == 0)
		ft_putendl_fd(msg, 2);
	else
		perror(msg);
	exit(1);
}

int		fdf_isspace(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\0')
		return (TRUE);
	return (FALSE);
}



