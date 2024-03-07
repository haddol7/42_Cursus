/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:54:28 by daeha             #+#    #+#             */
/*   Updated: 2024/03/07 21:04:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
1. File read
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
*/

#include "fdf.h" 

int main(int argc, char **argv)
{
	t_map map;

	read_map(argv[1], &map);
	return 0;
}
