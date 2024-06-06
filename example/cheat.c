#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>



int main(int argc, char **argv) {
	int pipefd[2];
	pid_t pid;

	// パイプの作成
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	// プロセスの複製
	pid = fork();

	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		// 子プロセス
		close(pipefd[0]);  // 読み取りエンドを閉じる

		write(pipefd[1], "< ", 2);
		write(pipefd[1], argv[1], strlen(argv[1]));
		int i = 2;
		while (i < argc - 2)
		{
			write(pipefd[1], " ", 1);
			write(pipefd[1], argv[i], strlen(argv[i]));
			write(pipefd[1], " |", 2);
			i++;
		}
		write(pipefd[1], " ", 1);
		write(pipefd[1], argv[argc - 2], strlen(argv[argc - 2]));
		write(pipefd[1], " > ", 3);
		write(pipefd[1], argv[argc - 1], strlen(argv[argc - 1]));
		
		close(pipefd[1]);  // 書き込みエンドを閉じる
		exit(EXIT_SUCCESS);
	} else {
		// 親プロセス
		close(pipefd[1]);  // 書き込みエンドを閉じる
		dup2(pipefd[0], STDIN_FILENO);

		//waitする前にあらかじめ読んで実行
		char *exe_argv[] = {"/bin/bash", NULL};
		char *exe_envp[] = {NULL};
		// execve関数を使用して新しいプログラムを実行
		if (execve("/bin/bash", exe_argv, exe_envp) == -1) {
			perror("execve");
			return 1;
		}

		close(pipefd[0]);  // 読み取りエンドを閉じる
		wait(NULL);  // 子プロセスの終了を待つ
		exit(EXIT_SUCCESS);
	}
}