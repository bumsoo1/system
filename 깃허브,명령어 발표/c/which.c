#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // access()

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <명령어>\n", argv[0]);
        return 1;
    }

    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "PATH 환경변수를 찾을 수 없습니다.\n");
        return 1;
    }

    char *path_copy = strdup(path_env);  // 수정 가능한 복사본
    if (path_copy == NULL) {
        perror("메모리 할당 실패");
        return 1;
    }

    char *token = strtok(path_copy, ":");

    while (token != NULL) {
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", token, argv[1]);

        if (access(fullpath, X_OK) == 0) {  // 실행 가능 여부 확인
            printf("%s\n", fullpath);
            free(path_copy);
            return 0;
        }

        token = strtok(NULL, ":");
    }

    printf("%s: 명령어를 찾을 수 없습니다.\n", argv[1]);

    free(path_copy);
    return 1;
}
