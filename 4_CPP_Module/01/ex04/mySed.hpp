/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mySed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:27:35 by daeha             #+#    #+#             */
/*   Updated: 2024/09/30 13:40:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>

class mySed
{
public:
	mySed(const std::string& filename);
	~mySed();
	void replace(const std::string& target, const std::string& replace);

private:
	std::ifstream	fin;
	std::ofstream	fout;
};
