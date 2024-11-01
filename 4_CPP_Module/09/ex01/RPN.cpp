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

bool	RPN::isoperator(char token)
{
	if (token == '+' || token == '-' || token == '/' || token == '*')
	{
		return (true);
	}
	return (false);
}

bool RPN::PushTokenAndCalculate(char token)
{
	int		lhs;
	int		rhs;
	size_t	size = mTokens.size();			

	if (!isnumber(token) && !isoperator(token))
	{
		return (false);
	}
	if (isnumber(token))
	{
		mTokens.push(token - '0');
	}
	else
	{
		if (size < 2)
		{
			return (false);
		}
		lhs = mTokens.top();
		mTokens.pop();
		rhs = mTokens.top();
		mTokens.pop();
		switch (token)
		{
		case '+':
			mTokens.push(rhs + lhs);
			break ;
		case '-':
			mTokens.push(rhs - lhs);
			break ;
		case '*':
			mTokens.push(rhs * lhs);
			break ;
		case '/':
			if (lhs == 0)
			{
				return (false);
			}
			mTokens.push(rhs / lhs);
			break ;
		}
	}
	return (true);
}

int RPN::GetResult() const
{
	return (mTokens.top());
}

size_t	RPN::GetSize() const
{
	return (mTokens.size());
}
