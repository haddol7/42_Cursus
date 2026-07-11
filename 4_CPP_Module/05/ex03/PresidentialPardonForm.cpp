#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
	: Form("default", 25, 5)
{

}

PresidentialPardonForm::PresidentialPardonForm(const std::string& name)
	: Form(name, 25, 5)
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& copy)
	: Form(copy.GetName(), 25, 5)
{
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const
{
	if (GetSign() == false)
	{
		throw (FormIsNotSigned());
	}	
	if (GetGradeToExecute() < executor.GetGrade())
	{
		throw (GradeTooLowException());
	}
	std::cout << GetName() << " is pardoned by Zaphod Beeblerox" << std::endl;
}
