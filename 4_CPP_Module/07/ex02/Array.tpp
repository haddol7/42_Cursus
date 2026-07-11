#include "Array.hpp"

template <typename T>
Array<T>::Array()
	: mArray(new T[0])
	, mSize(0)
{
	std::cout << "default construction" << std::endl;
}

template <typename T>
Array<T>::Array(unsigned int n)
	: mArray(new T[n])
	, mSize(n)
{
	std::cout << n << " sized construction" << std::endl;
}

template <typename T>
Array<T>::~Array()
{	
	std::cout << size() << " sized destruction" << std::endl;
	delete[] mArray;
}

template <typename T>
Array<T>::Array(const Array<T>& copy)
{
	mArray = NULL;
	*this = copy;
	std::cout << "copy construction" << std::endl;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
	if (this != &rhs)
	{
		delete[] mArray;
		mArray = new T[rhs.size()];
		mSize = rhs.size();
		for (unsigned int i = 0; i < rhs.size(); i++)
		{
			mArray[i] = rhs.mArray[i];
		}
		std::cout << "= operator" << std::endl;
	}
	return (*this);
}

template <typename T>
unsigned int Array<T>::size() const
{
	return (mSize);
}

template <typename T>
T& Array<T>::operator[](unsigned int n)
{
	if (n >= mSize || n < 0)
	{
		throw (std::out_of_range("out of range"));
	}
	return (mArray[n]);
}

template <typename T>
const T& Array<T>::operator[](unsigned int n) const
{
	if (n >= mSize || n < 0)
	{
		throw (std::out_of_range("out of range"));
	}
	return (mArray[n]);
}
