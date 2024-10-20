#pragma once

#include <cstddef>
#include <string>

template <typename T, typename Func>
void iter(T* ary, size_t len, Func func)
{
	for (size_t i = 0; i < len; ++i)
	{
		func(ary[i]);
	}
}

//부분 특수화
/*
template <typename T>
void iter(T* ary, size_t len, void (* func)(const std::string& a))
{
	for (size_t i = 0; i < len; ++i)
	{
		std::cout << i << "-th string : " << std::flush;
		func(ary[i]);
	}
}
*/
