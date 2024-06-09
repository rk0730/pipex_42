/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:33:52 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/09 18:27:32 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// argv[1]が"hear_doc"の時の呼ばれるもの
// argv[2]をlimiterとし、argv[argc-1]は追記リダイレクトで開いてそれをout_fd_pに入れる
// int	ft_hear_doc(int argc, char **argv, t_cmd_info *cmd_info_p, int *out_fd_p)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;
// 	char	*line;
// 	char	*limiter;

// 	if (argc == 2)
// 		return (1);
// 	pipe(pipe_fd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(pipe_fd[0]);
// 		limiter = ft_strjoin(argv[2], "\n");
// 		while (1)
// 		{
// 			ft_printf_fd(STDOUT_FILENO, "> ");
// 			line = get_next_line(STDIN_FILENO);
// 			if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
// 			{
// 				free(line);
// 				break ;
// 			}
// 			write(pipe_fd[1], line, ft_strlen(line));
// 			free(line);
// 		}
// 		close(pipe_fd[1]);
// 		free(limiter);
// 		exit(EXIT_SUCCESS);
// 	}
// 	close(pipe_fd[1]);
// 	wait(NULL);
// 	cmd_info_p->infile_fd = pipe_fd[0];
// 	if (argc == 3)
// 		return (1);
// 	*out_fd_p = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	if (*out_fd_p == -1)
// 		ft_printf_fd(STDERR_FILENO, "%s: %s\n", argv[argc - 1], strerror(errno));
// 	if (argc == 4)
// 		return (1);
// 	cmd_info_p->first_cmd = 3;
// 	cmd_info_p->argv = argv;
// 	return (0);
// }

// int	ft_check_arg(int argc, char **argv, t_cmd_info *cmd_info_p, int *out_fd_p)
// {
// 	if (argc == 1)
// 		return (1);
// 	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 		return (ft_hear_doc(argc, argv, cmd_info_p, out_fd_p));
// 	cmd_info_p->infile_fd = open(argv[1], O_RDONLY);
// 	if (cmd_info_p->infile_fd == -1)
// 		ft_printf_fd(STDERR_FILENO, "%s: %s\n", argv[1], strerror(errno));
// 	if (argc == 2)
// 		return (1);
// 	*out_fd_p = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (*out_fd_p == -1)
// 		ft_printf_fd(STDERR_FILENO, "%s: %s\n", argv[argc - 1], strerror(errno));
// 	if (argc == 3)
// 		return (1);
// 	cmd_info_p->first_cmd = 2;
// 	cmd_info_p->argv = argv;
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	char		**path_array;
	t_cmd_info	cmd_info;
	int			outfile_fd;

	if (ft_check_arg(argc, argv, &cmd_info, &outfile_fd))
		return (1);
	path_array = ft_gen_path_array(envp);
	cmd_info.path_array = path_array;

	// ft_printf_fd(STDERR_FILENO, "start ft_pipe infile: %d outfile: %d\n", cmd_info.infile_fd, outfile_fd);

	ft_pipe(cmd_info, argc - 2, outfile_fd); //cmd_count:最後に実行するコマンドの場所 argc-2、out_fd:outfileのfd
	// ft_printf_fd(STDERR_FILENO, "come back to main\n");


	ft_free_array(path_array);
	return (0);
}

// #include <libc.h>

// __attribute__((destructor))
// static void destructor()
// {
// 	system("leaks -q pipex");
// }