#pragma once

#include <cstdint>
#include "Data.hpp"

class Serializer
{
public:
	static uintptr_t	serialize(Data* ptr);
	static Data*		deserialize(uintptr_t raw);

private:
	Serializer();
	~Serializer();
	Serializer(const Serializer& copy);
	Serializer& operator=(const Serializer& rhs);
};
