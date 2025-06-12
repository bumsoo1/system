#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 1024  // 1KB씩 자르기

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("파일 열기 실패");
        return 1;
    }

    char buffer[CHUNK_SIZE];
    int part_num = 0;
    size_t nread;

    while ((nread = fread(buffer, 1, CHUNK_SIZE, src)) > 0) {
        char filename[256];
        snprintf(filename, sizeof(filename), "part_%03d", part_num++);

        FILE *dst = fopen(filename, "wb");
        if (!dst) {
            perror("출력 파일 생성 실패");
            fclose(src);
            return 1;
        }

        fwrite(buffer, 1, nread, dst);
        fclose(dst);
    }

    fclose(src);
    return 0;
}
