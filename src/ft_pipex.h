/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:36:15 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/18 18:35:49 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

typedef struct s_cmd_info
{
	char	**argv;
	char	**path_array;
	int		first_cmd;
	int		infile_fd;
}			t_cmd_info;

int			ft_check_arg(int argc, char **argv, t_cmd_info *cmd_info_p,
				int *out_fd_p);
char		**ft_gen_path_array(char **envp);
void		ft_free_array(char **array);
void		ft_exe_cmd(char *cmd, char **path_array);
void		ft_pipe(t_cmd_info cmd_info, int cmd_count, int out_fd);

#endif