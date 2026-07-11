#include "Serializer.hpp"

int main(void)
{
	Data		original;
	uintptr_t	original_ptr;

	original_ptr = Serializer::serialize(&original);
	std::cout << original << std::endl;
	original.SetX(06);
	original.SetY(01);
	std::cout << *Serializer::deserialize(original_ptr) << std::endl;
	
	if (&original == Serializer::deserialize(original_ptr))
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "KO" << std::endl;
		return (1);
	}
	return (0);
}

