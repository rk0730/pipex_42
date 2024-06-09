/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:33:52 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/09 20:53:09 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char		**path_array;
	t_cmd_info	cmd_info;
	int			outfile_fd;

	if (ft_check_arg(argc, argv, &cmd_info, &outfile_fd))
		return (1);
	path_array = ft_gen_path_array(envp);
	cmd_info.path_array = path_array;
	ft_pipe(cmd_info, argc - 2, outfile_fd);
	ft_free_array(path_array);
	return (0);
}

// #include <libc.h>

// __attribute__((destructor))
// static void destructor()
// {
// 	system("leaks -q pipex");
// }