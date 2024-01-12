/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:22:16 by daeha             #+#    #+#             */
/*   Updated: 2024/01/11 16:22:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	char	*result;
	int		fd;

	fd = open("test.txt");
	result = get_next_line(fd);

	return (0);
}