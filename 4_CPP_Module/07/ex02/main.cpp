#include <iostream>
#include "Array.hpp"

// void leaks()
// {
// 	system("leaks ex02");
// }

int main(void)
{
	// atexit(leaks);
	{
		Array<int> ary;

		try
		{
			ary[0] = 1;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	{
		Array<std::string> *str = new Array<std::string>(10);
		Array<std::string> str2;

		for (unsigned int i = 0; i < str->size(); i++)
		{
			(*str)[i] = "  : test";
			(*str)[i][0] = i + '0';
		}

		str2 = *str;
		(*str)[0] = "Deeeep copy";
		delete str;

		str2[9] = "9 : CPP Module 07 ex02";

		Array<std::string> str3(str2);
		str3[1] = "1 : Check for deep copy";
		str3[8] = "8 : OK";
		for (unsigned int i = 0; i < str2.size(); i++)
		{
			std::cout << "before - " << str2[i] << std::endl;
			std::cout << "after  - " << str3[i] << std::endl;
		}
	}
	std::cout << std::endl;
	{
		const Array<int> ary(10);

		//ary[0] = 10;

		std::cout << ary[0] << std::endl; 
	}
	return (0);
}

/*

#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;
}
*/
