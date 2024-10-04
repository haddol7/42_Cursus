/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:16:32 by daeha             #+#    #+#             */
/*   Updated: 2024/10/04 17:20:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria()
	: type("")
{
}

AMateria::AMateria(const AMateria& copy)
	: type(copy.getType())
{
}

AMateria::AMateria(const std::string& type)
	: type(type)
{
}

AMateria::~AMateria()
{
}

const std::string& AMateria::getType() const
{
	return (type);	
}
