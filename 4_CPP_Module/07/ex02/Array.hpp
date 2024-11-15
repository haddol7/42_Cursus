#pragma once

#include <exception>
#include <iostream>

template <typename T>
class Array
{
public:
	Array();
	Array(unsigned int n);
	~Array();
	Array(const Array& copy);
	Array& operator=(const Array& rhs);
	
	unsigned int	size() const;
	T&	operator[](unsigned int n);
	const T& operator[](unsigned int n) const;

private:
	T				*mArray;
	unsigned int	mSize;
};

#include "Array.tpp"
