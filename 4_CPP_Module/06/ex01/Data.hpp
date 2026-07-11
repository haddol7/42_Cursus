#pragma once

#include <iostream>

class Data
{
public:
	Data();
	~Data();
	Data(const Data& copy);
	Data& operator=(const Data& rhs);
	
	int		GetX() const;
	int		GetY() const;
	void	SetX(int x);
	void	SetY(int y);

private:
	int	mX;
	int	mY;	
};

std::ostream& operator<<(std::ostream& os, const Data& data);
