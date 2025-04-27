/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/23 11:40:00 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_find_and_exec(char *cmd, char **path_array)
{
	char	*tmp;
	char	*cmd_path;
	int		i;
	char	**exe_argv;

	i = 0;
	exe_argv = ft_split(cmd, ' ');
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i], "/");
		cmd_path = ft_strjoin(tmp, exe_argv[0]);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
		{
			if (execve(cmd_path, exe_argv, NULL) == -1)
				exit(EXIT_FAILURE);
		}
		free(cmd_path);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n", exe_argv[0]);
	ft_free_array(exe_argv);
	exit(EXIT_FAILURE);
}

static void	ft_exec_direct(char *cmd)
{
	char	**exe_argv;

	exe_argv = ft_split(cmd, ' ');
	if (execve(exe_argv[0], exe_argv, NULL) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd, strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_free_array(exe_argv);
}

void	ft_exe_cmd(char *cmd, char **path_array)
{
	if (ft_strchr(cmd, '/') != NULL)
		ft_exec_direct(cmd);
	else
		ft_find_and_exec(cmd, path_array);
}
