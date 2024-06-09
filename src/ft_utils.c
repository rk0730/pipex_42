/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:50:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/09 18:40:00 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	**ft_gen_path_array(char **envp)
{
	int i = 0;
	char **path_array;
	char *path;

	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			path_array = ft_split(path, ':');
			free(path);
			return (path_array);
		}
		i++;
	}
	path_array = (char **)malloc(sizeof(char *) * 1);
	path_array[0] = NULL;
	return (path_array);
}

void	ft_free_array(char **array)
{
	int i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
