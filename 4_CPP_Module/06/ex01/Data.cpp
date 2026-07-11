#include "Data.hpp"

Data::Data()
	: mX(42)
	, mY(21)
{
}

Data::~Data()
{
}

Data::Data(const Data& copy)
	: mX(copy.mX)
	, mY(copy.mY)
{
}

Data& Data::operator=(const Data& rhs)
{
	mX = rhs.mX;
	mY = rhs.mY;
	
	return (*this);
}

int Data::GetX() const
{
	return (mX);
}

int Data::GetY() const
{
	return (mY);
}

void Data::SetX(int x)
{
	mX = x;
}

void Data::SetY(int y) 
{
	mY = y;
}

std::ostream& operator<<(std::ostream& os, const Data& data)
{
	os << "X : " << data.GetX() << " Y: " << data.GetY();

	return (os);
}
