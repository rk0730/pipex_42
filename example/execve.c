#include <stdio.h>
#include <unistd.h>

int main() {
	char *argv[] = {"/bin/cat", NULL};
	char *envp[] = {NULL};

	// execve関数を使用して新しいプログラムを実行
	if (execve("/bin/cat", argv, envp) == -1) {
		// perror("execve");
		write(2, "command not found\n", 18);
		return 1;
	}

	// この行はexecveが成功した場合には実行されない
	printf("This line will not be printed if execve is successful.\n");

	return 0;
}
