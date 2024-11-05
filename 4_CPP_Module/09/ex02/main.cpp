#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

size_t	jacob(int i)
{
	return ((pow(2, i) - pow(-1, i)) / 3);
}

void print(const std::vector<int> &ary)
{
	for (size_t i = 0; i < ary.size(); i++)
	{
		std::cout << ary[i] << " ";
	}
	std::cout << std::endl;
}

void print(const std::vector<std::pair<int, int> > &ary)
{
	for (size_t i = 0; i < ary.size(); i++)
	{
		std::cout << ary[i].first;
		if (i + 1 != ary.size())
			std::cout << " --> ";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < ary.size(); i++)
	{
		std::cout << ary[i].second << "     ";
	}
	std::cout << std::endl;
}

// std::vector<int> fj(std::vector<int> &ary)
// {
// 	if (ary.size() == 0 || ary.size() == 1)
// 	{
// 		return ary;
// 	}
// 	if (ary.size() == 2)
// 	{
// 		std::vector<int> index_order;
// 		if (ary[0] > ary[1])
// 		{	
// 			index_order.push_back(1);
// 			index_order.push_back(0);
// 		}
// 		index_order.push_back(0);
// 		index_order.push_back(1);
// 		return ary;
// 	}

// 	std::vector<std::pair<int, int> >	chains;
// 	std::vector<std::pair<int, int> >	chain_order;
// 	std::vector<int>					result;
// 	std::vector<int> 					main_chain;

// 	for (size_t i = 1; i < ary.size(); i += 2)
// 	{
// 		if (ary[i] > ary[i - 1])
// 		{
// 			chains.push_back(std::pair<int,int>(ary[i], ary[i - 1]));
// 			main_chain.push_back(ary[i]);
// 		}
// 		else
// 		{
// 			chains.push_back(std::pair<int,int>(ary[i - 1], ary[i]));
// 			main_chain.push_back(ary[i - 1]);
// 		}
// 	}

// 	std::vector<int> ordered_main_chain_index;
// 	ordered_main_chain_index = fj(main_chain);

// 	chain_order = chains;
// 	for (size_t i = 0; i < main_chain.size(); i++)
// 	{
// 		chain_order[ordered_main_chain_index[i]] = chains[i];
// 	}
	
// 	print(chains);
// 	std::cout << std::endl;
// 	for (size_t i = 1; jacob(i - 1) < chains.size(); i++)
// 	{
// 		for (size_t j = jacob(i); j > jacob(i - 1); j--)
// 		{
// 			if (j > chains.size())
// 				j = chains.size();
// 			for (size_t k = 0; k < result.size(); k++)
// 			{
// 				if (chains[j - 1].second < result[k])
// 				{
// 					result.insert(result.begin() + k, chains[j - 1].second);
// 					break ;
// 				}
// 			}
// 			print(result);
// 		}
// 	}
// }

//<Value, Original Index>
//<Value, Index It have to be>
void fj(std::vector<std::pair<int, int> > &ary)
{
	if (ary.size() == 0 || ary.size() == 1)
	{
		return ;
	}
	if (ary.size() == 2)
	{
		if (ary[0].first > ary[1].first)
		{	
			std::swap(ary[0].second, ary[1].second);
		}
		return ;
	}

	std::vector<std::pair<int, int> >	chains;
	std::vector<std::pair<int, int> > 	main_chain;

	for (size_t i = 1; i < ary.size(); i += 2)
	{
		if (ary[i] > ary[i - 1])
		{
			chains.push_back(std::pair<int,int>(ary[i].first, ary[i - 1].first));
			main_chain.push_back(std::pair<int,int>(ary[i].first, --i));
		}
		else
		{
			chains.push_back(std::pair<int,int>(ary[i - 1].first, ary[i].first));
			main_chain.push_back(std::pair<int,int>(ary[i - 1].first, --i));
		}
		++i;
	}

	fj(main_chain);
	std::vector<std::pair<int, int> >	chains_order;
	for (size_t i = 0; i < main_chain.size(); i++)
	{
		chain_order[ordered_main_chain_index[i]] = chains[i];
	}
	
	print(chains);
	std::cout << std::endl;
	for (size_t i = 1; jacob(i - 1) < chains.size(); i++)
	{
		for (size_t j = jacob(i); j > jacob(i - 1); j--)
		{
			if (j > chains.size())
				j = chains.size();
			for (size_t k = 0; k < result.size(); k++)
			{
				if (chains[j - 1].second < result[k])
				{
					result.insert(result.begin() + k, chains[j - 1].second);
					break ;
				}
			}
			print(result);
		}
	}
}

int main()
{	
	std::vector<int>test;
	int test2[8] = {6, 4, 1, 3, 2, 7, 9, 8};

    for (int i = 0; i < 9; ++i) {
        test.push_back(test2[i]);
    }

	fj(test);
}
