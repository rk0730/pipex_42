#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#include "../libft/libft.h"

// pipex dirにいる状態で
// ccw example/cheat2.c ../libft/libft.a
// ./a.out infile.txt "ls -l" "grep .c" "wc -l" "cat -e" outfile.txt

int	main(int argc, char **argv)
{
	// "< argv[1] argv[2] | ... | argv[argc-2] > argv[argc-1]"という文字列を生成
	char	*tmp;
	char	*cmd;

	cmd = ft_strdup("< ");
	tmp = cmd;
	cmd = ft_strjoin(tmp, argv[1]);
	free(tmp);
	tmp = cmd;
	cmd = ft_strjoin(tmp, " ");
	free(tmp);
	int		i = 2;
	while (i < argc - 2)
	{
		tmp = cmd;
		cmd = ft_strjoin(tmp, argv[i]);
		free(tmp);
		tmp = cmd;
		cmd = ft_strjoin(tmp, " | ");
		free(tmp);
		i++;
	}
	tmp = cmd;
	cmd = ft_strjoin(tmp, argv[argc - 2]);
	free(tmp);
	tmp = cmd;
	cmd = ft_strjoin(tmp, " > ");
	free(tmp);
	tmp = cmd;
	cmd = ft_strjoin(tmp, argv[argc - 1]);
	free(tmp);
	// cmdを実行
	char	**exe_argv = (char **)malloc(sizeof(char *) * 4);
	exe_argv[0] = "/bin/bash";
	exe_argv[1] = "-c";
	exe_argv[2] = cmd;
	exe_argv[3] = NULL;
	char	**exe_envp = {NULL};
	if (execve("/bin/bash", exe_argv, exe_envp) == -1) {
		perror("execve");
		return 1;
	}
	return 0;
}