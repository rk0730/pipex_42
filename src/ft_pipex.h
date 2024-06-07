/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:36:15 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/07 11:56:10 by kitaoryoma       ###   ########.fr       */
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
#include "../ft_printf_fd/ft_printf.h"

char	**ft_gen_path_array(char **envp);
void	ft_free_array(char **array);
void	ft_exe_cmd(char *cmd, char **path_array);


#endif