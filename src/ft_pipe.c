/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:53:17 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/07 11:55:53 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

//まだ完成してない

ft_pipe(char **argv, char **path_array)
{
	int pipefd[2];
	pid_t pid1, pid2;

	// パイプの作成
	if (pipe(pipefd) == -1)
	{
		perror("pipe in ft_pipe");
		exit(EXIT_FAILURE);
	}

	// 子プロセスを作成
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork in ft_pipe");
		exit(EXIT_FAILURE);
	}
	else if (pid1 == 0)
	{
		// 子プロセス1
		int in_fd = open(argv[1], O_RDONLY);
		if (in_fd == -1)
		{
			perror("open infile");
			exit(EXIT_FAILURE);
		}

		dup2(in_fd, STDIN_FILENO);   // infileを標準入力にリダイレクト
		close(in_fd);
		dup2(pipefd[1], STDOUT_FILENO); // パイプの書き込みエンドを標準出力にリダイレクト
		close(pipefd[0]);
		close(pipefd[1]);

		// cmd1を実行
		ft_exe_cmd(argv[2], path_array);
	}

	// 2番目の子プロセスを作成
	if ((pid2 = fork()) == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid2 == 0)
	{
		// 子プロセス2
		int out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1)
		{
			perror("open outfile");
			exit(EXIT_FAILURE);
		}

		dup2(pipefd[0], STDIN_FILENO); // パイプの読み取りエンドを標準入力にリダイレクト
		close(pipefd[0]);
		close(pipefd[1]);
		dup2(out_fd, STDOUT_FILENO); // outfileを標準出力にリダイレクト
		close(out_fd);

		// cmd2を実行
		ft_exe_cmd(argv[3], path_array);
	}
	wait(NULL);
	wait(NULL);
}