#include <fstream>
#include <cstdlib>
#include <ctime>
#include "RobotomyRequestForm.hpp"

bool RobotomyRequestForm::mInitialized = false;

RobotomyRequestForm::RobotomyRequestForm()
	: Form("default", 72, 45)
{
	if (mInitialized == false)
	{
		mInitialized = true;
		srand(static_cast<unsigned int>(time(0)));
	}
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& name)
	: Form(name, 72, 45)
{
	if (mInitialized == false)
	{
		mInitialized = true;
		srand(static_cast<unsigned int>(time(0)));
	}
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy)
	: Form(copy.GetName(), 72, 45)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

void RobotomyRequestForm::execute(const Bureaucrat& executor) const
{
	if (GetSign() == false)
	{
		throw (FormIsNotSigned());
	}	
	if (GetGradeToExecute() < executor.GetGrade())
	{
		throw (GradeTooLowException());
	}
	
	std::cout << GetName();
	if (rand() % 2 == 0)
	{
		std::cout << " -> drrrrrrrrrrr..." << std::endl;
	}
	else
	{
		std::cout << " -> robotomy failed" << std::endl;
	}
}
