/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:36:38 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/23 11:43:31 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_first_cmd(t_cmd_info cmd_info, int cmd_count, int out_fd)
{
	if (cmd_info.infile_fd > 0)
	{
		dup2(cmd_info.infile_fd, STDIN_FILENO);
		close(cmd_info.infile_fd);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		ft_exe_cmd(cmd_info.argv[cmd_count], cmd_info.path_array);
	}
	exit(EXIT_FAILURE);
}

static void	ft_parent(t_cmd_info info, int count, int out_fd, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		if (out_fd > 0)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
			ft_exe_cmd(info.argv[count], info.path_array);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		wait(NULL);
		wait(NULL);
	}
}

static void	ft_recursive(t_cmd_info cmd_info, int cmd_count, int out_fd)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (cmd_count == cmd_info.first_cmd)
		ft_first_cmd(cmd_info, cmd_count, out_fd);
	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		ft_recursive(cmd_info, cmd_count - 1, pipe_fd[1]);
	else
		ft_parent(cmd_info, cmd_count, out_fd, pipe_fd);
}

void	ft_pipe(t_cmd_info cmd_info, int cmd_count, int outfile_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_recursive(cmd_info, cmd_count, outfile_fd);
	else
		wait(NULL);
}
