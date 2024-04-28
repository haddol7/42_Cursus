/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:12:06 by daeha             #+#    #+#             */
/*   Updated: 2024/04/28 15:27:48 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// $> ./pipex file1 cmd1 cmd2 file2

int main(int argc, char *argv[], char *envp[])
{
	t_pipe pipe;
	t_param	param;
	t_list	*path;
	
	if (argc < 5)
		return (terminate("test"));
	init_param(&pipe, &param, path);
	parse_envp_path(envp, path);
	execute_command(param, path, pipe);
	wait_command(argc);
	return (0);
}
