#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	// 標準出力を保存
	int saved_stdout = dup(STDOUT_FILENO);

	// 標準出力をファイルにリダイレクト
	if (dup2(fd, STDOUT_FILENO) == -1) {
		perror("dup2");
		close(fd);
		return 1;
	}

	// ファイルに書き込む
	printf("This will be written to the file.\n");

	// 元の標準出力を復元
	if (dup2(saved_stdout, STDOUT_FILENO) == -1) {
		perror("dup2");
		close(fd);
		return 1;
	}

	// 標準出力に書き込む
	printf("This will be written to the standard output.\n");

	close(fd);
	close(saved_stdout);
	return 0;
}
