#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <파일이름> <권한(8진수)>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    // 문자열 8진수 -> 정수 변환
    mode_t mode = strtol(argv[2], NULL, 8);

    if (chmod(filename, mode) == -1) {
        perror("chmod 실패");
        return 1;
    }

    return 0;
}
