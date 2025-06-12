#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void remove_recursive_force(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) {
        // 파일/디렉토리가 없거나 권한 문제라도 무시 (-f 옵션)
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        DIR *dir = opendir(path);
        if (!dir) {
            // 열기 실패해도 무시
            return;
        }

        struct dirent *entry;
        char fullpath[1024];

        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
            remove_recursive_force(fullpath);
        }

        closedir(dir);
        rmdir(path);  // 실패해도 무시
    } else {
        unlink(path);  // 실패해도 무시
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <삭제할 경로> [추가 경로...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        remove_recursive_force(argv[i]);
    }

    return 0;
}
