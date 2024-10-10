/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:21:19 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 20:24:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Brain
{
public:
	Brain();
	~Brain();
	Brain(const Brain& copy);
	Brain& operator=(const Brain& rhs);
private:
	std::string ideas[100];
};
