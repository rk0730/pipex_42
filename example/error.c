#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *file;

	// 存在しないファイルを開く
	file = fopen("non_existent_file.txt", "r");
	if (file == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}

	fclose(file);
	return EXIT_SUCCESS;
}

// #include <stdio.h>
// #include <string.h>
// #include <errno.h>

// int main() {
//     FILE *file;

//     // 存在しないファイルを開く
//     file = fopen("non_existent_file.txt", "r");
//     if (file == NULL) {
//         printf("Error opening file: %s\n", strerror(errno));
//         return 1;
//     }

//     fclose(file);
//     return 0;
// }