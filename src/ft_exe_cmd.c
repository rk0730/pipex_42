/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/08 13:28:16 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"




static int	ft_exe_rel_cmd(char *cmd, char **path_array)
{
	char	*tmp;
	char	*full_cmd;
	int		i;
	char	**exe_argv;

	i = 0;
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i], "/");
		full_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		exe_argv = ft_split(full_cmd, ' ');
		//実行可能かどうか確認する
		if (access(exe_argv[0], X_OK) == 0)
		{
			if (execve(exe_argv[0], exe_argv, NULL) == -1)
			{
				perror("execve in ft_exe_rel_cmd");
			}
		}
		free(full_cmd);
		ft_free_array(exe_argv);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd);
	perror("command not found in ft_exe_rel_cmd");
	return (-1);
}

int	ft_exe_cmd(char *cmd, char **path_array)
{
	char	**exe_argv;

	if (*cmd == '/')
	{
		//絶対パス
		exe_argv = ft_split(cmd, ' ');
		if (execve(exe_argv[0], exe_argv, NULL) == -1)
		{
			perror("execve in ft_exe_cmd");
			ft_printf_fd(STDERR_FILENO, "%s: %s", cmd, strerror(errno));
		}
		ft_free_array(exe_argv);
	}
	else
	{
		// 相対パス
		ft_exe_rel_cmd(cmd, path_array);
	}
	return (-1);
}