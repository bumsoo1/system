#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void remove_recursive(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) {
        perror("stat 실패");
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        // 디렉토리면 내부 항목 먼저 삭제
        DIR *dir = opendir(path);
        if (!dir) {
            perror("디렉토리 열기 실패");
            return;
        }

        struct dirent *entry;
        char fullpath[1024];

        while ((entry = readdir(dir)) != NULL) {
            // . , .. 는 건너뛰기
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
            remove_recursive(fullpath);
        }

        closedir(dir);

        // 디렉토리 비우고 난 뒤 삭제
        if (rmdir(path) != 0)
            perror("디렉토리 삭제 실패");
    } else {
        // 일반 파일이나 링크 삭제
        if (unlink(path) != 0)
            perror("파일 삭제 실패");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <삭제할 경로>\n", argv[0]);
        return 1;
    }

    remove_recursive(argv[1]);
    return 0;
}
