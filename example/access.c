#include <stdio.h>
#include <unistd.h>

int main() {
	const char *file_path = "example.txt";

	// ファイルが存在するかチェック
	if (access(file_path, F_OK) == 0) {
		printf("File exists.\n");

		// ファイルが読み取り可能かチェック
		if (access(file_path, R_OK) == 0) {
			printf("File is readable.\n");
		} else {
			printf("File is not readable.\n");
		}

		// ファイルが書き込み可能かチェック
		if (access(file_path, W_OK) == 0) {
			printf("File is writable.\n");
		} else {
			printf("File is not writable.\n");
		}

		// ファイルが実行可能かチェック
		if (access(file_path, X_OK) == 0) {
			printf("File is executable.\n");
		} else {
			printf("File is not executable.\n");
		}
	} else {
		printf("File does not exist.\n");
	}

	return 0;
}
