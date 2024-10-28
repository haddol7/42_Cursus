#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}
	
RPN::RPN(const RPN& copy)
{
	mTokens = copy.mTokens;
}
	
RPN& RPN::operator=(const RPN& rhs)
{
	if (this != &rhs)
	{
		mTokens = rhs.mTokens;
	}
	return (*this);
}

bool RPN::PushToken(char token)
{
	static const char op[4] = {'+', '-', '/', '*'};

	if (!isnumber(token) || token != '+' || token != '-' || token != '/' || token != '*')
	{
		return (false);
	}
	mTokens.push(token);
	return (true);
}
	
long long RPN::Calculate()
{

}

