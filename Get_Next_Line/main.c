/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:22:16 by daeha             #+#    #+#             */
/*   Updated: 2024/01/18 23:33:59 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	char	*result;
	char	buf[10];
	int		fd;
	int		fd2;
	int		fd3;

//	fd = open("/Users/daeha/francinette/tests/get_next_line/gnlTester/files/41_with_nl", O_RDONLY);
//	fd2 = open("/Users/daeha/francinette/tests/get_next_line/gnlTester/files/42_with_nl", O_RDONLY);

	fd = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test2.txt", O_RDONLY);
	result = get_next_line(123);
	printf("%s", result);
	result = get_next_line(fd2);
	printf("%s", result);
	result = get_next_line(123);
	printf("%s", result);
	result = get_next_line(fd2);
	printf("%s", result);
	result = get_next_line(123);
	printf("%s", result);
	return (0);
}
