#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <원본파일/디렉토리> <목적지>\n", argv[0]);
        return 1;
    }

    if (rename(argv[1], argv[2]) != 0) {
        perror("이동 실패");
        return 1;
    }

    return 0;
}
