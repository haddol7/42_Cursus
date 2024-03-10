/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:08:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/10 21:45:58 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

void	check_leaks(void)
{
	system("leaks fdf");
}

static char	*read_map_as_one_line(int fd);
static void	check_map_size(char *content, t_map *map);
//static void	transform_map(char *content, t_map *map);
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
// void	load_map(char *dir, t_map *map)
// {
// 	int		fd;
// 	char	*content;

// 	fd = open(dir, O_RDONLY);
// 	content = read_map_as_one_line(fd);
// 	check_map_size(content, map);
// 	transform_map(content, map); 
	
// 	free(content);
// 	close(fd);
// }

static char	*read_map_as_one_line(int fd)
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

static void	check_map_size(char *str, t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	map->x_size = 0;
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\n' && (*(str + 1) == ' ' || \
											*(str + 1) == '\n' || \
											*(str + 1) == '\0'))
			x++;
		if (*str == '\n')
		{
			if (x != map->x_size && map->x_size != 0)
				ft_printf("format_error\n");
			if (map->x_size == 0)
				map->x_size = x;
			x = 0;
			y++;
		}
		str++;
	}
	map->y_size = y;
}

// static void	transform_map(char *content, t_map *map)
// {
// 	return ;
// }

int main(int argc, char **argv)
{
	int	fd;
	t_map	map;
	char	*test;
	
	if (argc != 2)
		return 0;
	
	fd = open(argv[1], O_RDONLY);
	test = read_map_as_one_line(fd);
	ft_printf("read_done!\n", test);
	
	check_map_size(test, &map);
	ft_printf("%u %u\n", map.x_size, map.y_size);
	
	free(test);
	atexit(check_leaks);
}
