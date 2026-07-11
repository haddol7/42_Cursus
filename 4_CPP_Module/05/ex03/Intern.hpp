#pragma once
#include <exception>
#include <string>
#include "Form.hpp"

class Intern
{
public:
	Intern();
	~Intern();
	Form* makeForm(const std::string& form, const std::string& target) const;

	class InvalidForm : public std::exception 
	{
	public:
		virtual const char* what() const throw()
		{
			return ("there is no Form");
		}
	};

private:
	Intern(const Intern& copy);
	Intern& operator=(const Intern& rhs);
};
