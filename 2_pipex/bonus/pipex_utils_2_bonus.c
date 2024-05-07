/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:16:28 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 22:06:06 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	control_fildes(int fd_a[2], int fd_b[2], t_param arg, int n)
{
	if (n % 2 == 0)
	{
		if (n != 2)
		{
			close(fd_a[0]);
			close(fd_a[1]);
		}
		if (n + arg.here_doc == arg.argc - 2)
			return ;
		if (pipe(fd_a) == -1)
			parent_error(arg, n);
	}
	else
	{
		if (n != 3)
		{
			close(fd_b[0]);
			close(fd_b[1]);
		}
		if (n + arg.here_doc == arg.argc - 2)
			return ;
		if (pipe(fd_b) == -1)
			parent_error(arg, n);
	}
}

char	*find_path(char *cmd, char **pathv)
{
	char	*path;
	char	*cmd_trim;
	int		i;

	cmd_trim = extract_first_command(cmd);
	i = -1;
	while (pathv[++i] != NULL)
	{
		if (!access(cmd_trim, F_OK | X_OK))
			return (cmd_trim);
	}
	i = -1;
	while (pathv[++i] != NULL)
	{	
		path = ft_strjoin(pathv[i], cmd_trim);
		if (!access(path, F_OK | X_OK))
		{
			free(cmd_trim);
			return (path);
		}
		free(path);
	}
	free(cmd_trim);
	terminate("pipex : command not found");
	return (NULL);
}

char	**parse_envp_path(char *envp[])
{
	int		i;
	char	*str_path;

	if (envp == NULL)
		terminate("pipex : No such file or directory");
	str_path = NULL;
	i = 0;
	while (envp[i])
	{	
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			str_path = envp[i] + 5;
			break;
		}
		i++;
	}
	if (!str_path)
		terminate("pipex : No such file or directory");
	return (ft_split(str_path, ':'));
}

void	close_remainder_fds(int fd_a[2], int fd_b[2], int n)
{
	if (n % 2 == 1)
	{
		close(fd_b[0]);
		close(fd_b[1]);
	}
	else
	{
		close(fd_a[0]);
		close(fd_a[1]);
	}
}
