/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:36:52 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 01:20:58 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include "Fixed.hpp"

const int Fixed::mBits = 8;

Fixed::Fixed()
	: mValue(0)
{
}

Fixed::~Fixed()
{
}

Fixed::Fixed(const int num)
{
	mValue = num << mBits;
}

Fixed::Fixed(const float num)
{
	mValue = roundf(num * (1 << mBits));
}

Fixed::Fixed(const Fixed& copy)
{
	*this = copy;
}

Fixed& Fixed::operator=(const Fixed &rhs)
{
	if (this != &rhs)
		mValue = rhs.mValue;
	return (*this);
}

Fixed Fixed::operator+(const Fixed& rhs) const
{
	Fixed	result(this->toFloat() + rhs.toFloat());

	return (result);
}

Fixed Fixed::operator-(const Fixed& rhs) const
{
	Fixed	result(this->toFloat() - rhs.toFloat());

	return (result);
}

Fixed Fixed::operator*(const Fixed& rhs) const
{
	Fixed	result(this->toFloat() * rhs.toFloat());
	
	return (result);
}

Fixed Fixed::operator/(const Fixed& rhs) const
{
	Fixed	result(this->toFloat() / rhs.toFloat());

	return (result);
}

bool Fixed::operator<(const Fixed &rhs) const
{
	return (this->getRawBits() < rhs.getRawBits());
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return (this->getRawBits() <= rhs.getRawBits());
}

bool Fixed::operator>(const Fixed &rhs) const
{
	return (this->getRawBits() > rhs.getRawBits());
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return (this->getRawBits() >= rhs.getRawBits());
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return (this->getRawBits() == rhs.getRawBits());
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return (this->getRawBits() != rhs.getRawBits());
}

Fixed& Fixed::operator++()
{
	this->mValue++;
	return (*this);
}

Fixed& Fixed::operator--()
{
	this->mValue++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed result(*this);
	
	result.mValue = this->mValue++;
	return (result);
}

Fixed Fixed::operator--(int)
{
	Fixed result(*this);
	
	result.mValue = this->mValue--;
	return (result);
}

Fixed& Fixed::min(Fixed &ref1, Fixed &ref2)
{
	if (ref1.mValue < ref2.mValue)
		return (ref1);
	return (ref2);
}

Fixed& Fixed::max(Fixed &ref1, Fixed &ref2)
{
	if (ref1.mValue > ref2.mValue)
		return (ref1);
	return (ref2);
}

const Fixed& Fixed::min(const Fixed &ref1, const Fixed &ref2)
{
	if (ref1.mValue < ref2.mValue)
		return (ref1);
	return (ref2);
}

const Fixed& Fixed::max(const Fixed &ref1, const Fixed &ref2)
{
	if (ref1.mValue > ref2.mValue)
		return (ref1);
	return (ref2);
}

int Fixed::getRawBits() const
{
	return (mValue);
}

void Fixed::setRawBits(int const raw)
{
	mValue = raw;
}

float Fixed::toFloat() const
{
	return (static_cast<float>(mValue) / (1 << mBits));
}

int Fixed::toInt() const
{
	return (mValue >> mBits);
}

std::ostream& operator<<(std::ostream& output, const Fixed& rhs)
{
	output << rhs.toFloat();
	return (output);
}
