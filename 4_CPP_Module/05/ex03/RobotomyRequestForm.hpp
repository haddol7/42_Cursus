# pragma once

#include "Form.hpp"

class RobotomyRequestForm : public Form
{
public:
	RobotomyRequestForm();
	RobotomyRequestForm(const std::string& name);
	~RobotomyRequestForm();
	RobotomyRequestForm(const RobotomyRequestForm& copy);
	RobotomyRequestForm& operator=(const RobotomyRequestForm& rhs);

	virtual void execute(const Bureaucrat& executor) const;
private:
	static bool mInitialized;
};
