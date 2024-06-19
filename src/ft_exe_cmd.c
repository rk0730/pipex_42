/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/19 11:23:00 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_exe_rel_cmd(char *cmd, char **path_array)
{
	char	*tmp;
	char	*cmd_path;
	int		i;
	char	**exe_argv;

	//PATHから検索する
	i = 0;
	while (path_array[i])
	{
		exe_argv = ft_split(cmd, ' ');
		tmp = ft_strjoin(path_array[i], "/");
		cmd_path = ft_strjoin(tmp, exe_argv[0]);
		free(tmp);
		//実行可能かどうか確認する
		if (access(cmd_path, X_OK) == 0)
		{
			if (execve(cmd_path, exe_argv, NULL) == -1)
			{
				perror("execve in ft_exe_rel_cmd");
				exit(EXIT_FAILURE);
			}
		}
		free(cmd_path);
		ft_free_array(exe_argv);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd);
	exit(EXIT_FAILURE);
}

void	ft_exe_cmd(char *cmd, char **path_array)
{
	char	**exe_argv;

	//直接実行可能
	exe_argv = ft_split(cmd, ' ');
	if (access(exe_argv[0], X_OK) == 0)
	{
		if (execve(exe_argv[0], exe_argv, NULL) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "%s: %s", cmd, strerror(errno));
			perror("execve in ft_exe_cmd");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_exe_rel_cmd(cmd, path_array);
	}
	ft_free_array(exe_argv);
}
