#pragma once
#include <stack>

class RPN
{
public:
	RPN();
	~RPN();
	RPN(const RPN& copy);
	bool		PushToken(char token);
	long long	Calculate();
	RPN& operator=(const RPN& rhs);

private:
	std::stack<char> mTokens;	
};
