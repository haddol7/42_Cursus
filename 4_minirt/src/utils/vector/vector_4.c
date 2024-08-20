/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:07:37 by daeha             #+#    #+#             */
/*   Updated: 2024/08/20 17:20:30 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

t_vec3	vunit(t_vec3 vec)
{
	double	len;

	len = vlength(vec);
	if (len == 0)
	{
		ft_memset(&vec, 0, sizeof(t_vec3));
		return (vec);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vec3	vmin(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}
