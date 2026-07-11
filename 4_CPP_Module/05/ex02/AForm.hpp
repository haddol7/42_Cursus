#pragma once

#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
public:
	AForm();
	AForm(const std::string& name, int gradeSign, int gradeExec);
	virtual ~AForm();
	AForm(const AForm& copy);
	AForm& operator=(const AForm& rhs);

	const std::string& GetName(void) const;
	bool GetSign(void) const;
	int GetGradeToSign(void) const;
	int GetGradeToExecute(void) const;
	
	void beSigned(const Bureaucrat& bureaucrat);
	virtual void execute(const Bureaucrat& executor) const = 0;

	class GradeTooHighException : public std::exception 
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Grade Too HIGH");
		}
	};
	class GradeTooLowException : public std::exception 
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Grade Too LOW");
		}
	};
	class FormIsNotSigned : public std::exception 
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Form Is Not SIGNED");
		}
	};

private:
	const std::string	mName;
	bool				mSign;
	const int			mGradeToSign;
	const int			mGradeToExecute;
};

std::ostream& operator<<(std::ostream& out, const AForm& rhs);
