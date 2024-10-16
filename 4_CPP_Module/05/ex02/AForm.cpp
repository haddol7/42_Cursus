#include "AForm.hpp"

AForm::AForm()
	: mName("default")
	, mSign(false)
	, mGradeToSign(1)
	, mGradeToExecute(0)
{
}

AForm::AForm(const std::string& name, int gradeSign, int gradeExec)
	: mName(name)
	, mSign(false)
	, mGradeToSign(gradeSign)
	, mGradeToExecute(gradeExec)
{
}

AForm::~AForm()
{
}

AForm::AForm(const AForm& copy)
	: mName(copy.GetName())
	, mSign(copy.GetSign())
	, mGradeToSign(copy.GetGradeToSign())
	, mGradeToExecute(copy.GetGradeToExecute())
{
}

AForm& AForm::operator=(const AForm& rhs)
{
	if (this != &rhs)
	{
		mSign = rhs.GetSign();
	}
	return (*this);
}

const std::string& AForm::GetName(void) const
{
	return (mName);
}

bool AForm::GetSign(void) const
{
	return (mSign);
}

int AForm::GetGradeToSign(void) const
{
	return (mGradeToSign);
}

int AForm::GetGradeToExecute(void) const
{
	return (mGradeToExecute);
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.GetGrade() > GetGradeToSign())
	{
		throw (GradeTooLowException());
	}
	mSign = true;
}

std::ostream& operator<<(std::ostream& out, const AForm& rhs)
{
	std::cout << rhs.GetName() << " - signed status is " << std::boolalpha <<  rhs.GetSign() << ", grade to sign is " << rhs.GetGradeToSign() << ", grade to execute is " << rhs.GetGradeToExecute();  

	return (out);
}
