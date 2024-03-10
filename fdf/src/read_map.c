/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:08:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/10 20:05:30 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

// void	check_leaks(void)
// {
// 	system("leaks fdf");
// }

/* 
load_map(char *str, t_map *map)

	call read_map function to read .fdf files.
	
	when a file is given below,
	1	2	3
	4	5	6
	7	8	9
	
	map.data is initialized like
	map.data[0].x = 0 | map.data[0].y = 0 | map.data[0].z = 1
	map.data[1].x = 1 | map.data[1].y = 0 | map.data[1].z = 2
	map.data[2].x = 2 | map.data[2].y = 0 | map.data[2].z = 3
	...

	and map.x_size and map.y_size are initialized by 3.

Subject consider all given map files as well formatted. But function should handle
errors

1. system-call function error
2. map file format error
*/
void	load_map(char *dir, t_map *map)
{
	int		fd;
	char	*content;

	fd = open(dir, O_RDONLY);
	content = read_map_all(fd);
	check_map(content, map);
	transform_map(content, map); 
	
	free(content);
	close(fd);
}

static char	*read_map_all(int fd)
{
	int		read_size;
	char	buffer[FDF_BUFFER_SIZE];
	char	*temp;
	char	*res;

	temp = ft_strdup("");
	read_size = read(fd, buffer, FDF_BUFFER_SIZE);
	while (read_size != 0)
	{
		buffer[read_size] = '\0';
		res = ft_strjoin(temp, buffer);
		free(temp);
		temp = res;
		read_size = read(fd, buffer, FDF_BUFFER_SIZE);
	}
	return (res);
}

static void	check_map(char *content, t_map *map)
{
	return ;
}

static void	transform_map(char *content, t_map *map)
{
	return ;
}

int main()
{
	int	fd;
	char	*test;
	fd = open("test.txt", O_RDONLY);

	test = read_map_all(fd);
	ft_printf("%s", test);
	free(test);
}
