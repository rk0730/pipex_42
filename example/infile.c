#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void execute_command_with_input(const char *infile, const char *cmd1) {
	pid_t pid = fork();

	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		// 子プロセス
		// infileを開く
		int in_fd = open(infile, O_RDONLY);
		if (in_fd == -1) {
			perror("open infile");
			exit(EXIT_FAILURE);
		}

		// 標準入力をinfileにリダイレクト
		if (dup2(in_fd, STDIN_FILENO) == -1) {
			perror("dup2");
			close(in_fd);
			exit(EXIT_FAILURE);
		}
		close(in_fd);

		// cmd1を実行
		execl("/bin/bash", "bash", "-c", cmd1, (char *)NULL);

		// execveが戻った場合はエラー
		perror("execl");
		exit(EXIT_FAILURE);
	} else {
		// 親プロセス
		wait(NULL); // 子プロセスの終了を待つ
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s infile cmd1\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	const char *infile = argv[1];
	const char *cmd1 = argv[2];

	execute_command_with_input(infile, cmd1);

	return 0;
}
