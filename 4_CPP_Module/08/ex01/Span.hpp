#pragma once
#include <cstddef>
#include <vector>

class Span
{
public:
	Span(unsigned int size);
	Span(const Span& copy);
	Span& operator=(const Span& rhs);
	~Span();

	void			addNumber(int num);
	unsigned long	shortestSpan(void) const;
	unsigned long	longestSpan(void) const;

	template <typename Iter>
	void			addNumbers(Iter first, Iter last);

private:
	Span();
	unsigned int		mCapacity;
	unsigned int		mSize;
	std::vector<int>	mVector;
};

template <typename Iter>
void Span::addNumbers(Iter first, Iter last)
{
	unsigned int	range = std::distance(first, last);
	if (mSize + range > mCapacity)
	{
		throw std::out_of_range("Index out of range");
	}
	mVector.insert(mVector.end(), first, last);
	mSize += range;
}
