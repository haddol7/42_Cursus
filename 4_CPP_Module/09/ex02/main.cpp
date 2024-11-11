#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
#include <ctime>
#include <iomanip>

#define JACOPSTHAL(i) (((1 << ((i) + 1)) + ((i) % 2 == 0 ? 1 : -1)) / 3)

typedef	std::pair<int, size_t> 											t_pair_value_index;
typedef std::vector<t_pair_value_index>									t_vec_value_index;
typedef std::vector<std::pair<t_pair_value_index, t_pair_value_index> >	t_vec_main_sub_chain_index;
typedef std::list<t_pair_value_index>									t_list_value_index;
typedef std::list<std::pair<t_pair_value_index, t_pair_value_index> >	t_list_main_sub_chain_index;

void print_vector(std::vector<int> ary)
{
	for (size_t i = 0; i < ary.size(); i++)
		std::cout << ary[i] << " ";
	std::cout << std::endl;
}

//TODO : 인덱스 범위 탐색 수정
t_vec_value_index::iterator binary_search(t_vec_value_index &result, int value)
{
	size_t left = 0;
	size_t right = result.size();

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (result[mid].first < value)
			left = mid + 1;
		else
			right = mid;
	}
	return result.begin() + left;
}

void	ford_johnson(t_vec_value_index &ary)
{
	size_t	size = ary.size();

	if (size <= 1)
		return ;
	else if (size == 2)
	{
		if (ary[0].first > ary[1].first)
			std::swap(ary[0].second, ary[1].second);
		return ;
	}
	t_vec_main_sub_chain_index	whole_chain;
	t_vec_value_index		main_chain;

	whole_chain.reserve(size / 2);
	main_chain.reserve(size / 2);
	for (size_t i = 0; i < size / 2; ++i)
	{
		if (ary[i * 2].first > ary[i * 2 + 1].first)
		{
			whole_chain.push_back(std::make_pair(std::make_pair(ary[i * 2].first, i * 2), std::make_pair(ary[i * 2 + 1].first, i * 2 + 1)));
			main_chain.push_back(std::make_pair(ary[i * 2].first, i));
		}
		else
		{
			whole_chain.push_back(std::make_pair(std::make_pair(ary[i * 2 + 1].first, i * 2 + 1), std::make_pair(ary[i * 2].first, i * 2)));
			main_chain.push_back(std::make_pair(ary[i * 2 + 1].first, i));
		}
	}

	ford_johnson(main_chain);
	t_vec_main_sub_chain_index	sorted_whole_chain;
	t_vec_value_index 		result;

	sorted_whole_chain.resize(size / 2);
	result.reserve(size);
	for (size_t i = 0; i < size / 2; ++i)
		sorted_whole_chain[main_chain[i].second] = whole_chain[i];
	for (size_t i = 0; i < size / 2; ++i)
		result.push_back(sorted_whole_chain[i].first);
	bool 	loop = true;
	size_t	i = 2;
	result.insert(result.begin(), sorted_whole_chain[0].second);
	do
	{
		size_t	ford_i = std::min(static_cast<size_t>(JACOPSTHAL(i)), size / 2 - 1);
		if (ford_i == size / 2 - 1)
			loop = false;
		for (; ford_i > static_cast<size_t>(JACOPSTHAL(i - 1)) || ford_i == 1; --ford_i)
			result.insert(binary_search(result, sorted_whole_chain[ford_i].second.first), sorted_whole_chain[ford_i].second);
		i++;
	} while (loop);
	if (size % 2 == 1)
		result.insert(binary_search(result, ary[size - 1].first), ary[size - 1]);
	for (size_t j = 0; j < size; ++j)
		ary[result[j].second].second = j;
}

void	fj_sort(std::vector<int> &ary)
{
	clock_t start = clock();

	t_vec_value_index ary_index;
	ary_index.reserve(ary.size());
	for (size_t i = 0; i < ary.size(); ++i)
	{
		ary_index.push_back(std::make_pair(ary[i], i));
	}
	ford_johnson(ary_index);
	for (size_t i = 0; i < ary.size(); ++i)
	{
		ary[ary_index[i].second] = ary_index[i].first;
	}
    clock_t end = clock();
    double elapsed_us = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << std::fixed << std::setprecision(0);
    std::cout << "Elapsed time: " << elapsed_us << " us" << std::endl;
}

int main(int argc, char *argv[])
{
	std::vector<int> test;
	std::vector<int> test2;

	for (int i = 1; i < argc; ++i)
	{	
		test.push_back(atoi(argv[i]));
	}
	test2 = test;
	//print_vector(test);
	clock_t start = clock();
	std::sort(test2.begin(), test2.end());
	clock_t end = clock();
	double elapsed_us = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << std::fixed << std::setprecision(0);
    std::cout << "Elapsed time: " << elapsed_us << " us" << std::endl;
	fj_sort(test);
	print_vector(test);
}
