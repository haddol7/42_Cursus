#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base*	generate(void);
void	identify(Base *p);
void	identify(Base &p);

int main()
{
	Base* test;
	
	srand(time(NULL));
	for (int i = 0; i < 5 ; ++i)
	{
		std::cout << std::endl << i << "-th test" << std::endl;
		test = generate();
		identify(test);
		delete test;
	}
	return (0);
}

Base*	generate(void)
{
	int	random_value = (rand() % 3);

	switch (random_value)
	{
	case 0:
		std::cout << "generated A" << std::endl;
		return (new A);
	case 1:
		std::cout << "generated B" << std::endl;
		return (new B);
	case 2:
		std::cout << "generated C" << std::endl;
		return (new C);
	default:
		assert(false);
		return (0);
	}
}

void	identify(Base *p)
{
	if (dynamic_cast<A*>(p))
	{
		std::cout << "class is A" << std::endl;
	}
	else if (dynamic_cast<B*>(p))
	{
		std::cout << "class is B" << std::endl;
	}
	else if (dynamic_cast<C*>(p))
	{
		std::cout << "class is C" << std::endl;
	}
	else
	{
		assert(false);
	}
}

void	identify(Base &p)
{
	if (dynamic_cast<A*>(&p))
	{
		std::cout << "class is A" << std::endl;
	}
	else if (dynamic_cast<B*>(&p))
	{
		std::cout << "class is B" << std::endl;
	}
	else if (dynamic_cast<C*>(&p))
	{
		std::cout << "class is C" << std::endl;
	}
	else
	{
		assert(false);
	}
}
