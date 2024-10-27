#pragma once
#include <stack>
#include <deque>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
	MutantStack();
	virtual ~MutantStack();
	MutantStack(const MutantStack& copy);
	MutantStack& operator=(const MutantStack& rhs);

	typedef typename std::deque<T>::iterator				iterator;
	typedef typename std::deque<T>::reverse_iterator		reverse_iterator;
	typedef typename std::deque<T>::const_iterator			const_iterator;
	typedef typename std::deque<T>::const_reverse_iterator	const_reverse_iterator;

	iterator				begin();
	iterator				end();
	reverse_iterator		rbegin();
	reverse_iterator		rend();
	const_iterator			cbegin();
	const_iterator 			cend();
	const_reverse_iterator	crbegin();
	const_reverse_iterator	crend();

protected:
	using std::stack<T>::c;
};

#include "MutantStack.tpp"
