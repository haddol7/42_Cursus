#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main()
{
	ShrubberyCreationForm	home("Home");
	RobotomyRequestForm		robot("Robot");
	PresidentialPardonForm	presi("President");

	Bureaucrat	intern("Intern", 150);
	Bureaucrat	junior("Junior", 130);
	Bureaucrat	senior("Senior", 70);
	Bureaucrat	director("Director", 25);
	Bureaucrat	ceo("CEO", 1);

	std::cout << "==============FORM==============" << std::endl;
	std::cout << home << std::endl;
	std::cout << robot << std::endl;
	std::cout << presi << std::endl;

	std::cout << "===========Bureaucrat===========" << std::endl;
	std::cout << intern << std::endl;
	std::cout << junior << std::endl;
	std::cout << senior << std::endl;
	std::cout << director << std::endl;
	std::cout << ceo << std::endl;

	std::cout << "===========ShrubberyCreationForm============" << std::endl;
	intern.signForm(home); //grade low exeception
	junior.signForm(home);
	intern.executeForm(home); //grade low exeception
	junior.executeForm(home);

	std::cout << "===========RobotomyRequestForm==============" << std::endl;
	senior.executeForm(robot); // not signed execption
	senior.signForm(robot);
	director.executeForm(robot); // not signed execption
	ceo.executeForm(robot); // not signed execption

	std::cout << "===========PresidentialPardonForm===========" << std::endl;
	director.signForm(presi);
	director.executeForm(presi); //grade low exeception
	ceo.executeForm(presi);

	std::cout << "==============AFTER FORM==============" << std::endl;
	std::cout << home << std::endl;
	std::cout << robot << std::endl;
	std::cout << presi << std::endl;

	return (0);
}
