#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp) {
	char *argv_p[] = {"/bin/ls", "-l", NULL};
	char *envp_p[] = {NULL};

	int i = -1;
	while (envp[++i])
		envp[i] = NULL;
	// execve関数を使用して新しいプログラムを実行
	if (execve("/bin/ls", argv_p, envp) == -1) {
		// perror("execve");
		write(2, "command not found\n", 18);
		return 1;
	}

	// この行はexecveが成功した場合には実行されない
	printf("This line will not be printed if execve is successful.\n");

	return 0;
}
