#pragma once

#include <exception>
#include <iostream>

template <typename T>
class Array
{
public:
	Array();
	Array(int n);
	~Array();
	Array(const Array& copy);
	Array& operator=(const Array& rhs);
	
	int	size() const;
	T&	operator[](int n);
	const T& operator[](int n) const;

private:
	T	*mArray;
	int	mSize;
};

#include "Array.tpp"
