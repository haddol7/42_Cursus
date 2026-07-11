/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:21:19 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 21:20:02 by daeha            ###   ########.fr       */
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
	void setIdea(const int idx, const std::string& str);
	const std::string& getIdea(const int idx) const;
private:
	std::string ideas[100];
};
