/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:17:59 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 23:56:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	std::ifstream	fin;
	std::ofstream	fout;
	std::string		filename;
	std::string		target;
	std::string		replace;
	std::string		line;
	
	if (argc != 4)
		return (1);
	filename = argv[1];
	target = argv[2];
	replace = argv[3];
	fin.open(filename);
	fout.open(filename + ".replace");
	
	while (!fin.eof())
	{
		if (fin.fail() || fout.fail())
		{
			std::cerr << "file read failure" << std::endl;
			return (1);
		}
		std::getline(fin, line);
		if (line != "")
			fout << line << std::endl;
	}
	
	fin.close();
	fout.close();
	return (0);
}
