#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void usage(const char *prog) {
    fprintf(stderr, "사용법: %s <파일 또는 디렉토리>\n", prog);
    exit(1);
}

unsigned long filesize(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) {
        perror("stat 실패");
        return 0;
    }
    return st.st_size;
}

int main(int argc, char *argv[]) {
    if (argc != 2) usage(argv[0]);
    unsigned long sz = filesize(argv[1]);
    printf("%lu\t%s\n", sz, argv[1]);
    return 0;
}