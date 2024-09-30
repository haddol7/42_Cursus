/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:38:56 by daeha             #+#    #+#             */
/*   Updated: 2024/09/30 15:17:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Harl
{
public:
	Harl();
	~Harl();
	void complain(std::string level);
	bool filter(const std::string& level);
private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);
};
