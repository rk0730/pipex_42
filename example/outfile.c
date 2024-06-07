#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void execute_command_with_output(const char *cmd, const char *outfile) {
	pid_t pid = fork();

	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		// 子プロセス
		// outfileを開く
		int out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1) {
			perror("open outfile");
			exit(EXIT_FAILURE);
		}

		// 標準出力をoutfileにリダイレクト
		if (dup2(out_fd, STDOUT_FILENO) == -1) {
			perror("dup2");
			close(out_fd);
			exit(EXIT_FAILURE);
		}
		close(out_fd);

		// cmdを実行
		execl("/bin/bash", "bash", "-c", cmd, (char *)NULL);

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
		fprintf(stderr, "Usage: %s cmd outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	const char *cmd = argv[1];
	const char *outfile = argv[2];

	execute_command_with_output(cmd, outfile);

	return 0;
}
