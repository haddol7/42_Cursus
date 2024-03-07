/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:08:28 by daeha             #+#    #+#             */
/*   Updated: 2024/03/05 20:51:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
* 1. read .fdf files
* 2. use get_next_line
* 3. store data called by gnl as linked list
*/
static void		fdf_lstadd_back(t_file **line_list, char *line)
{
	t_file	*last;
	t_file	*temp;

	temp = malloc(sizeof(t_file));
	//malloc error
	temp->data = line;
	temp->next = NULL;
	if (*line_list == NULL)
		*line_list = temp;
	else
	{
		*last = ft_lstlast(*line_list);
		last->next = temp;
	}
}

static t_file	*read_raw_file(char *dir, t_map *map)
{
	t_file	*line_list;
	int		fd;
	char	*line;

	map->y_size = 0;
	fd = open(dir, O_RDONLY);
	//open error
	line_list = NULL;
	while (1)
	{
		line = get_next_line(fd);
		//gnl error

		if (*line == '\0')
			break;
		fdf_lstadd_back(&line_list, line);
		(map->y_size)++;
	}
	return (line_list);
}

static void make_data_free_list(t_file **line_list, t_map *map)
{
	t_file	*temp;
	int		i;

	i = 0;
	map->data = malloc(sizeof(int *) * map->y_size);
	//malloc error

	while (i < map->y_size)
	{
		map->data[i] = split_in_atoi((*line_list)->data, map);
		temp = *line_list;
		*line_list = (*line_list)->next;
		free(temp->data);
		free(temp);
		i++;
	}
}

void	parse_map_data(t_map *map, char *dir)
{
	t_file	*line_list;

	line_list = read_raw_file(dir, map);

	make_data_free_list(&line_list, map);
}

