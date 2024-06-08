/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:36:15 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/08 20:55:46 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <stdio.h>
# include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <fcntl.h>

#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

typedef struct s_cmd_info
{
	// int		argc;
	int		first_cmd;
	char	**argv;
	char	**path_array;
	int		infile_fd;
	// int		outfile_fd;
} t_cmd_info;


char	**ft_gen_path_array(char **envp);
void	ft_free_array(char **array);
void	ft_exe_cmd(char *cmd, char **path_array);
void	ft_recursive(t_cmd_info cmd_info, int cmd_count, int out_fd);
void	ft_pipe(t_cmd_info cmd_info, int cmd_count, int out_fd);

#endif