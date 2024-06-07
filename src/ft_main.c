/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:33:52 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/07 21:02:30 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**path_array;

	if (argc == 0)
	{
		argc = 0;
		ft_printf("%s\n", argv[0]);
	}
	//----------------------------------------------------------------
	// エラー処理
	if (argc != 5)
	{
		ft_printf_fd(STDERR_FILENO, "Usage: %s file1 cmd1 cmd2 file2\n",
			argv[0]);
		return (1);
	}
	path_array = ft_gen_path_array(envp);

	ft_pipe(argv, path_array);


	//再帰関数
	// ft_recursive(cmd_info, cmd_count, out_fd); cmd_count:最後に実行するコマンドの場所 argc-2、out_fd:outfileのfd



	ft_free_array(path_array);
	return (0);
}

// #include <libc.h>

// __attribute__((destructor))
// static void destructor()
// {
// 	system("leaks -q pipex");
// }