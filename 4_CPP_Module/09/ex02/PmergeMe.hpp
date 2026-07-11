#pragma once

#include <vector>
#include <list>

class PmergeMe
{
public:
	PmergeMe(int argc, char *argv[]);
	~PmergeMe();
	void sort();
	static void	print_vector(std::vector<int> &ary);
	static void	print_vector(std::list<int> &ary);
	static void sort_with_clock(std::vector<int> &ary);
	static void sort_with_clock(std::list<int> &ary);

private:
	PmergeMe();
	PmergeMe(const PmergeMe& cpy);
	PmergeMe& operator=(const PmergeMe& rhs);

	std::vector<int>	mArrayVector;
	std::list<int>		mArrayList;
};
