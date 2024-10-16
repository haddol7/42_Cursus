# pragma once

#include "Form.hpp"

class ShrubberyCreationForm : public Form
{
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(const std::string& name);
	~ShrubberyCreationForm();
	ShrubberyCreationForm(const ShrubberyCreationForm& copy);
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& rhs);

	virtual void execute(const Bureaucrat& executor) const;
};
