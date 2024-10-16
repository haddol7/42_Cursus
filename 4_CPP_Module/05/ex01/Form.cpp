#include "Form.hpp"

Form::Form()
	: mName("default")
	, mSign(false)
	, mGradeToSign(1)
	, mGradeToExecute(0)
{
}

Form::Form(const std::string& name, int grade)
	: mName(name)
	, mSign(false)
	, mGradeToSign(grade)
	, mGradeToExecute(0)
{
	if (grade < HIGHEST_GRADE)
	{
		throw GradeTooHighException();
	}
	else if (grade > LOWEST_GRADE)
	{
		throw GradeTooLowException();
	}
}

Form::~Form()
{
}

Form::Form(const Form& copy)
	: mName(copy.GetName())
	, mSign(copy.GetSign())
	, mGradeToSign(copy.GetGradeToSign())
	, mGradeToExecute(copy.GetGradeToExecute())
{
}

Form& Form::operator=(const Form& rhs)
{
	if (this != &rhs)
	{
		mSign = rhs.GetSign();
	}
	return (*this);
}

const std::string& Form::GetName(void) const
{
	return (mName);
}

bool Form::GetSign(void) const
{
	return (mSign);
}

int Form::GetGradeToSign(void) const
{
	return (mGradeToSign);
}

int Form::GetGradeToExecute(void) const
{
	return (mGradeToExecute);
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.GetGrade() > GetGradeToSign())
	{
		throw (GradeTooLowException());
	}
	mSign = true;
}

std::ostream& operator<<(std::ostream& out, const Form& rhs)
{
	std::cout << rhs.GetName() << " - signed status is " << std::boolalpha <<  rhs.GetSign() << ", grade to sign is " << rhs.GetGradeToSign() << ", grade to execute is " << rhs.GetGradeToExecute();  

	return (out);
}
