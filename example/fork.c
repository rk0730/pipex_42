#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t pid;

	// forkシステムコールを呼び出して新しいプロセスを作成
	pid = fork();

	if (pid < 0) {
		// forkが失敗した場合
		perror("fork");
		return 1;
	} else if (pid == 0) {
		// 子プロセスの場合
		printf("This is the child process. PID: %d\n", getpid());
	} else {
		// 親プロセスの場合
		printf("This is the parent process. PID: %d, Child PID: %d\n", getpid(), pid);
	}

	return 0;
}
