#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <파일1> [파일2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        // unlink() 호출, 실패해도 에러 출력 안 함
        unlink(argv[i]);
    }

    return 0;
}
