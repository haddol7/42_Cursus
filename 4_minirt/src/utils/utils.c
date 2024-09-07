/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:12 by daeha             #+#    #+#             */
/*   Updated: 2024/09/07 16:04:30 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	simple_rand(void)
{
	static int	seed = SEED;

	seed = (1103515245 * seed + 12345) % 2147483648;
	return (seed);
}

double	drandom(void)
{
	return ((float)simple_rand() / (RAND_MAX));
}

double	drandom_(double min, double max)
{
	return (min + (max - min) * drandom());
}
