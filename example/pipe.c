#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "get_next_line/get_next_line.h"

// ccw example/pipe.c example/get_next_line/* && ./a.out

int main() {
	int pipefd[2];
	pid_t pid;
	char buf;

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

		// const char *msg = "Hello from child!";
		// write(pipefd[1], msg, strlen(msg));
		char *line;
		while ((line = get_next_line(STDIN_FILENO))!= NULL) {
			write(pipefd[1], line, strlen(line));
			free(line);
		}
		close(pipefd[1]);  // 書き込みエンドを閉じる
		exit(EXIT_SUCCESS);
	} else {
		// 親プロセス
		close(pipefd[1]);  // 書き込みエンドを閉じる

		printf("Parent process reading from pipe:\n");
		while (read(pipefd[0], &buf, 1) > 0) {
			write(STDOUT_FILENO, &buf, 1);
		}
		//waitする前にあらかじめ読んで実行することがポイント

		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);  // 読み取りエンドを閉じる
		wait(NULL);  // 子プロセスの終了を待つ
		exit(EXIT_SUCCESS);
	}
}
