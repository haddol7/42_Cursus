/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:15:24 by daeha             #+#    #+#             */
/*   Updated: 2024/10/01 00:06:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point()
	: mX(0)
	, mY(0)
{
}

Point::Point(const float x, const float y)
	: mX(x)
	, mY(y)
{
}

Point::Point(const Point& copy)
	: mX(copy.getX())
	, mY(copy.getY())
{
}

Point& Point::operator=(const Point& rhs)
{
	if (this != &rhs)
	{
		const_cast<Fixed&>(mX) = rhs.getX();
		const_cast<Fixed&>(mY) = rhs.getY();
	}
	return (*this);
}

Point Point::operator-(const Point& rhs) const
{
	Point	result(this->getX() - rhs.getX(), this->getY() - rhs.getY());
	
	return (result);
}

Point::~Point()
{
}

float Point::getX() const
{
	return (mX.toFloat());	
}

float Point::getY() const
{
	return (mY.toFloat());
}

float Point::cross(const Point& u, const Point& v)
{
	return (u.getX() * v.getY() - u.getY() * v.getX());
}
