/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:36:38 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/08 13:25:16 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_recursive(t_cmd_info cmd_info, int cmd_count, int out_fd)
{
	int pipe_fd[2];
	pid_t pid;

	// 最初のコマンド
	if (cmd_count == cmd_info.first_cmd)
	{
		if (cmd_info.infile_fd > 0)
		{
			dup2(cmd_info.infile_fd, STDIN_FILENO);
			close(cmd_info.infile_fd);
			dup2(out_fd, STDOUT_FILENO);
			ft_exe_cmd(cmd_info.argv[cmd_count], cmd_info.path_array);
		}
		close(out_fd);
		ft_printf_fd(STDERR_FILENO, "first command in ft_recursive: %s\n", cmd_info.argv[cmd_count]);
		exit(EXIT_FAILURE);
	}
	//最初以外のコマンド
	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork in ft_recursive");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)//子プロセス
	{
		ft_recursive(cmd_info, cmd_count - 1, pipe_fd[1]);
	}
	//親プロセス
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	// ft_printf_fd(STDERR_FILENO, " out_fd: %d\n", out_fd);
	if (out_fd > 0)
	{
		dup2(out_fd, STDOUT_FILENO);
		ft_exe_cmd(cmd_info.argv[cmd_count], cmd_info.path_array);
		close(out_fd);
	}
	wait(NULL);
	ft_printf_fd(STDERR_FILENO, "in ft_recursive: %s\n", cmd_info.argv[cmd_count]);
	exit(EXIT_FAILURE);	
}