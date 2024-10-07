/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:30:14 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 21:27:54 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

typedef Point Vector;

bool bsp(const Point a, const Point b, const Point c, const Point point)
{
	Vector	ab(b - a);
	Vector	bc(c - b);
	Vector	ca(a - c);
	Vector	ap(a - point);
	Vector	bp(b - point);
	Vector	cp(c - point);
	float	ab_pa = Point::cross(ab, ap);
	float	bc_pb = Point::cross(bc, bp); 
	float	ca_pc = Point::cross(ca, cp);

	if ((ab_pa > 0 && bc_pb > 0 && ca_pc > 0) ||
		(ab_pa < 0 && bc_pb < 0 && ca_pc < 0))
		return (true);
	return (false);
}
