#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    const char *dir_path = ".";
    if (argc > 1) dir_path = argv[1];

    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("디렉토리 열기 실패");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);  // 숨김파일 포함해서 모두 출력
    }

    closedir(dir);
    return 0;
}
