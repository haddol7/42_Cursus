#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat daeha("daeha", 10);
	Form contract("contract", 10);

	std::cout << contract << std::endl;
	daeha.signForm(contract);
	std::cout << contract << std::endl;
	daeha.DecrementGrade();
	daeha.signForm(contract);

	return (0);
}
