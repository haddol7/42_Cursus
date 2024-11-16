#pragma once
#include <stack>
#include <cstddef>

class RPN
{
public:
	RPN();
	~RPN();
	bool		PushTokenAndCalculate(char token);
	int			GetResult() const;
	size_t		GetSize() const;
	static bool	isoperator(char token);

private:
	RPN(const RPN& copy);
	RPN& operator=(const RPN& rhs);
	
	std::stack<unsigned long> mTokens;	
};
