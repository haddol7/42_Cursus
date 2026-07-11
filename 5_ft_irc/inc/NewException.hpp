#pragma once

#include <iostream>

class NewException
{
	public :
		virtual	~NewException() throw() {}
		virtual std::string	what() const throw() {return (std::string(""));}
};
