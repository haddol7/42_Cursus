#include <cctype>
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

	if (!isdigit(token) && !isoperator(token))
	{
		return (false);
	}
	if (isdigit(token))
	{
		mTokens.push(token - '0');
	}
	else
	{
		if (size < 2)
		{
			return (false);
		}
		rhs = mTokens.top();
		mTokens.pop();
		lhs = mTokens.top();
		mTokens.pop();
		switch (token)
		{
		case '+':
			mTokens.push(lhs + rhs);
			break ;
		case '-':
			mTokens.push(lhs - rhs);
			break ;
		case '*':
			mTokens.push(lhs * rhs);
			break ;
		case '/':
			if (rhs == 0)
			{
				return (false);
			}
			mTokens.push(lhs / rhs);
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
