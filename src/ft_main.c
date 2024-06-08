/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:33:52 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/08 21:37:26 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**path_array;
	t_cmd_info	cmd_info;
	int		outfile_fd;

	if (argc == 0)
	{
		argc = 0;
		ft_printf("%s\n", argv[0]);
	}
	// エラー処理
	// if (argc < 4)
	// {
	// 	ft_printf_fd(STDERR_FILENO, "Usage: %s file1 cmd1 ... cmdn file2\n",
	// 		argv[0]);
	// 	return (1);
	// }
	//----------------------------------------------------------------
	path_array = ft_gen_path_array(envp);

	// ft_pipe(argv, path_array);
	// argcいらなそう
	// cmd_info.argc = argc;
	// 6/8 argc==1でinfileが存在しない場合はここでreturnする
	cmd_info.first_cmd = 2;
	cmd_info.argv = argv;
	cmd_info.path_array = path_array;
	cmd_info.infile_fd = open(argv[1], O_RDONLY);
	if (cmd_info.infile_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", argv[1], strerror(errno));
	}
	// ft_printf_fd(STDERR_FILENO, "argv[argc-1]: %s\n", argv[argc-1]);
	// 6/8 argcが少なく、outfileが存在しない場合はここでreturnする
	outfile_fd = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//outfileがひらけなかった時のエラーメッセージ
	if (outfile_fd == -1)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", argv[argc - 1], strerror(errno));
	// 6/8 argc==3で実行するコマンドが一つもない場合はここでreturnする
	ft_pipe(cmd_info, argc - 2, outfile_fd); //cmd_count:最後に実行するコマンドの場所 argc-2、out_fd:outfileのfd
	ft_printf_fd(STDERR_FILENO, "come back to main\n");


	ft_free_array(path_array);
	return (0);
}

#include <libc.h>

__attribute__((destructor))
static void destructor()
{
	system("leaks -q pipex");
}