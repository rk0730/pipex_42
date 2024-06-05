#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// プロセスの生成と表示を再帰的に行う関数
void create_processes(int current, int max) {
	if (current > max) {
		return;
	}

	printf("%d\n", current);

	pid_t pid = fork();

	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		// 子プロセス
		create_processes(current + 1, max);
		exit(EXIT_SUCCESS);
	} else {
		// 親プロセス
		wait(NULL);  // 子プロセスの終了を待つ
	}
}

int main() {
	int max_processes = 5;  // ここで生成するプロセス数を指定

	create_processes(0, max_processes);

	return 0;
}
