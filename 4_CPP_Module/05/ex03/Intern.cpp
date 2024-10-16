#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{

}

Intern::~Intern()
{
}

Intern::Intern(const Intern& copy)
{
	if (this != &copy)
	{
	}
}

Intern& Intern::operator=(const Intern& rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

Form* Intern::makeForm(const std::string& form, const std::string& target) const
{
	int	i;
	const std::string	forms[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};

	for (i = 0; i < 3; i++)
	{
		if (form == forms[i])
		{
			break;
		}
	}
	if (i != 3)
	{
		std::cout << "Intern creates " << form << std::endl; 
	}
	switch (i)
	{
		case 0:
			return (new ShrubberyCreationForm(target));
		case 1:
			return (new RobotomyRequestForm(target));
		case 2:
			return (new PresidentialPardonForm(target));
		default:
			throw (InvalidForm());
	}
}
