/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:53:17 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/08 21:35:34 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// void	ft_pipe(char **argv, char **path_array)
// {
// 	int pipe_fd[2];
// 	pid_t pid;

// 	// パイプの作成
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("pipe in ft_pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	// forkする
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork in ft_pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		// 子プロセス
// 		close(pipe_fd[0]);
// 		int in_fd = open(argv[1], O_RDONLY);
// 		if (in_fd == -1)
// 		{
// 			perror("open infile in ft_pipe");
// 			exit(EXIT_FAILURE);
// 		}

// 		dup2(in_fd, STDIN_FILENO);  // infileを標準入力にリダイレクト
// 		close(in_fd);  //これここ？
// 		dup2(pipe_fd[1], STDOUT_FILENO); // パイプの書き込みエンドを標準出力にリダイレクト

// 		// cmd1を実行
// 		ft_exe_cmd(argv[2], path_array);
// 		close(pipe_fd[1]);
// 	}

// 	// 親プロセス
// 	close(pipe_fd[1]);
// 	int out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (out_fd == -1)
// 	{
// 		perror("open outfile in ft_pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(pipe_fd[0], STDIN_FILENO); // パイプの読み取りエンドを標準入力にリダイレクト
// 	dup2(out_fd, STDOUT_FILENO); // outfileを標準出力にリダイレクト
// 	//cmd2を実行
// 	ft_exe_cmd(argv[3], path_array);
// 	close(pipe_fd[0]);
// 	wait(NULL);
// }


//最後のコマンドを実行する関数　それ以外のコマンドはft_recursiveに実行させる
void	ft_pipe(t_cmd_info cmd_info, int cmd_count, int out_fd)
{
	int pipe_fd[2];
	pid_t pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork in ft_pipe");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)//子プロセス
	{
		//最後のコマンドの入力を決める
		//最後のコマンドが最初のコマンドでもある場合（コマンドが1個）
		if (cmd_count == cmd_info.first_cmd)
		{
			dup2(cmd_info.infile_fd, STDIN_FILENO);
			close(cmd_info.infile_fd);
		}
		else
		{
			ft_recursive(cmd_info, cmd_count - 1, pipe_fd[1]);
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		}
		//最後のコマンドを実行する、exitはしない
		if (out_fd > 0)
		{
			dup2(out_fd, STDOUT_FILENO);
			ft_exe_cmd(cmd_info.argv[cmd_count], cmd_info.path_array);
			close(out_fd);
		}
	}
	//親プロセス
	wait(NULL);
	ft_printf_fd(STDERR_FILENO, "ft_pipe done\n");
}