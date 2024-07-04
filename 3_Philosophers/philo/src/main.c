/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:46:31 by daeha             #+#    #+#             */
/*   Updated: 2024/07/04 21:46:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void leaks(void)
{
	system("leaks philo");
}

int main(int argc, char **argv)
{
	t_stat	stat;
	
	//atexit(leaks);
	if(!init(argc, argv, &stat))
		return (1);
	free_resource(&stat);
	return (0);
}
