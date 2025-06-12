#include <stdio.h>
#include <dirent.h>  // 디렉토리 관련 함수
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *path = ".";  // 기본 경로는 현재 디렉토리

    if (argc > 1) {
        path = argv[1];  // 인자가 있으면 해당 경로 사용
    }

    DIR *dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "디렉토리 열기 오류: %s\n", strerror(errno));
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // 현재 디렉토리(.)와 부모 디렉토리(..)는 건너뛰기 원하면 제거 가능
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
