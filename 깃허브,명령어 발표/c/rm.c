#include <stdio.h>
#include <unistd.h>  // unlink 함수
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <파일 이름>\n", argv[0]);
        return 1;
    }

    int ret = unlink(argv[1]);  // 파일 삭제
    if (ret == -1) {
        fprintf(stderr, "파일 삭제 오류: %s\n", strerror(errno));
        return 1;
    }

    printf("파일 '%s'가 삭제되었습니다.\n", argv[1]);
    return 0;
}
