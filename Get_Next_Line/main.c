/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:22:16 by daeha             #+#    #+#             */
/*   Updated: 2024/01/12 21:47:10 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	char	*result;
	char	buf[10];
	int		fd;
	int		fd2;

	fd = open("./test.txt", O_RDONLY);

	result = get_next_line(fd);
	printf("%s", result);
	result = get_next_line(fd);
	printf("%s", result);
	return (0);
}
