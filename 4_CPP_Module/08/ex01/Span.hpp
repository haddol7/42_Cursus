#pragma once
#include <cstddef>
#include <vector>

class Span
{
public:
	Span(size_t size);
	Span(const Span& copy);
	Span& operator=(const Span& rhs);
	~Span();

	void			addNumber(int num);
	unsigned long	shortestSpan(void) const;
	unsigned long	longestSpan(void) const;

private:
	Span();
	size_t				mCapacity;
	size_t				mSize;
	std::vector<int>	mVector;
};
