#include <stdio.h>
#include <sys/stat.h>  // mkdir 함수
#include <sys/types.h> // mode_t 타입
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("사용법: mkdir 디렉토리명\n");
        return 1;
    }

    // 디렉토리 생성 (권한 0755)
    if (mkdir(argv[1], 0755) == -1) {
        fprintf(stderr, "mkdir 오류: %s\n", strerror(errno));
        return 1;
    }

    printf("'%s' 디렉토리를 생성했습니다.\n", argv[1]);
    return 0;
}
