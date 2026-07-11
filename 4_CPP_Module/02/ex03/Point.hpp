/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:07:47 by daeha             #+#    #+#             */
/*   Updated: 2024/09/30 23:55:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

class Point
{
public:
	Point();
	Point(const float x, const float y);
	Point(const Point& copy);
	Point& operator=(const Point& rhs);
	Point operator-(const Point& rhs) const;
	float getX(void) const;
	float getY(void) const;
	static float cross(const Point& a, const Point& b);
	~Point();

private:
	const Fixed mX;
	const Fixed mY;
};

bool bsp(const Point a, const Point b, const Point c, const Point point);
