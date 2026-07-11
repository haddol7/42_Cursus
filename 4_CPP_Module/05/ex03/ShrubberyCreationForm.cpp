#include <fstream>
#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
	: Form("default", 145, 137)
{

}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& name)
	: Form(name, 145, 137)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& copy)
	: Form(copy.GetName(), 145, 137)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const
{
	if (GetSign() == false)
	{
		throw (FormIsNotSigned());
	}
	if (GetGradeToExecute() < executor.GetGrade())
	{
		throw (GradeTooLowException());
	}

	std::ofstream	fout;
	std::string		filename = GetName() + "_shrubbery";
	
	fout.open(filename.c_str());
	if (fout.is_open() == false)
	{
		throw (std::ios_base::failure("file open failure"));
	}

	fout <<	"              _{\\ _{\\{\\/}/}/}__\n"
            "             {/{/\\}{/{/\\}(\\}{/\\} _\n"
            "            {/{/\\}{/{/\\}(_)}{/{/\\}  _\n"
            "         {\\{/(\\}\\}{/{/\\}\\}{/){/\\}\\} /\\}\n"
            "        {/{/(_)/}{\\{/)\\}{\\(_){/}/}/}/}\n"
            "       _{\\{/{/{\\{/{/(_)/}/}/}{\\(/}/}/}\n"
            "      {/{/{\\{\\{\\(/}{\\{\\/}/}{\\}(_){\\/}\\}\n"
            "      _{\\{/{\\{/(_)}{/}{/{/\\}\\})\\}{/\\}\n"
            "     {/{/{\\{\\(/}{/{\\{\\{\\/})/}{\\(_)/}/}\\}\n"
            "      {\\{\\/}(_){\\{\\{\\/}/}(_){\\/}{\\/}/})/}\n"
            "       {/{\\{\\/}{/{\\{\\{\\/}/}{\\{\\/}/}\\}(_)\n"
            "      {/{\\{\\/}{/){\\{\\{\\/}/}{\\{(/}/}\\}/}\n"
            "       {/{\\{\\/}(_){\\{\\{(/}/}{\\(_)/}/}\\}\n"
            "         {/(\\{/{\\{/{\\{\\/}(_){\\/}/}\\}/}(\\}\n"
            "          (_){/{\\/}{\\{\\/}/}{\\{)/}/}(_)\n"
            "            {/{/{\\{\\/}{/{\\{\\{(_)/}\n"
            "             {/{\\{\\{\\/}/}{\\{\\\\}/}\n"
            "              {){/ {\\/}{\\/} \\}\\}\n"
            "              (_)  \\.-'.-/\n"
            "          __...--- |'-.-'| --...__\n"
            "   _...--\"   .-'   |'-.-'|  ' -.  \"\"--..__\n"
            " -\"    ' .  . '    |.'-._| '  . .  '   jro\n"
            " .  '-  '    .--'  | '-.'|    .  '  . '\n"
            "          ' ..     |'-_.-|\n"
            "  .  '  .       _.-|-._ -|-._  .  '  .\n"
            "              .'   |'- .-|   '.\n"
            "  ..-'   ' .  '.   `-._.-'   .'  '  - .\n"
            "   .-' '        '-._______.-'     '  .\n"
            "        .      ~,\n"
            "    .       .   |\\   .    ' '-.\n"
            "    ___________/  \\____________\n"
            "   /                           \\\n"
            "  |        CPP_MODULE 05        |\n"
            "   \\___________________________/\n" << std::endl;
	fout.close();
}
