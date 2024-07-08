/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:46:31 by daeha             #+#    #+#             */
/*   Updated: 2024/07/08 18:39:05 by daeha            ###   ########.fr       */
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
	//create_monitor_thread(&stat);
	create_philos_threads(&stat);
	free_resources(&stat);
	return (0);
}
