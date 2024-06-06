#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

void execute_command_chain(const char *infile, const char *cmd1, const char *cmd2, const char *outfile) {
	int pipefd[2];
	pid_t pid1, pid2;

	// パイプの作成
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	// 最初の子プロセスを作成
	if ((pid1 = fork()) == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid1 == 0) {
		// 子プロセス1
		int in_fd = open(infile, O_RDONLY);
		if (in_fd == -1) {
			perror("open infile");
			exit(EXIT_FAILURE);
		}

		dup2(in_fd, STDIN_FILENO);   // infileを標準入力にリダイレクト
		close(in_fd);
		dup2(pipefd[1], STDOUT_FILENO); // パイプの書き込みエンドを標準出力にリダイレクト
		close(pipefd[0]);
		close(pipefd[1]);

		// cmd1を実行
		execl("/bin/bash", "bash", "-c", cmd1, (char *)NULL);
		perror("execl");
		exit(EXIT_FAILURE);
	}

	// 2番目の子プロセスを作成
	if ((pid2 = fork()) == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid2 == 0) {
		// 子プロセス2
		int out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1) {
			perror("open outfile");
			exit(EXIT_FAILURE);
		}

		dup2(pipefd[0], STDIN_FILENO); // パイプの読み取りエンドを標準入力にリダイレクト
		close(pipefd[0]);
		close(pipefd[1]);
		dup2(out_fd, STDOUT_FILENO); // outfileを標準出力にリダイレクト
		close(out_fd);

		// cmd2を実行
		execl("/bin/bash", "bash", "-c", cmd2, (char *)NULL);
		perror("execl");
		exit(EXIT_FAILURE);
	}

	// 親プロセス
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0); // 最初の子プロセスの終了を待つ
	waitpid(pid2, NULL, 0); // 2番目の子プロセスの終了を待つ
}

int main(int argc, char *argv[]) {
	if (argc != 5) {
		fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	const char *infile = argv[1];
	const char *cmd1 = argv[2];
	const char *cmd2 = argv[3];
	const char *outfile = argv[4];

	execute_command_chain(infile, cmd1, cmd2, outfile);

	return 0;
}
