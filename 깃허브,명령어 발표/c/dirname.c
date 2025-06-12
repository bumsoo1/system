#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <경로>\n", argv[0]);
        return 1;
    }

    char path[1024];
    strncpy(path, argv[1], sizeof(path));
    path[sizeof(path) - 1] = '\0';  // 널 종료 보장

    char *last_slash = strrchr(path, '/');

    if (last_slash != NULL) {
        if (last_slash == path) {
            // 루트 디렉토리(/)만 있는 경우
            printf("/\n");
        } else {
            *last_slash = '\0';  // 마지막 '/' 이후 제거
            printf("%s\n", path);
        }
    } else {
        // '/'가 없으면 현재 디렉토리
        printf(".\n");
    }

    return 0;
}
