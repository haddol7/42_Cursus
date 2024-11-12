#pragma once
#include <stack>
#include <cstddef>

class RPN
{
public:
	RPN();
	~RPN();
	RPN(const RPN& copy);
	bool		PushTokenAndCalculate(char token);
	int			GetResult() const;
	size_t		GetSize() const;
	static bool	isoperator(char token);
	RPN& operator=(const RPN& rhs);

private:
	std::stack<int> mTokens;	
};
