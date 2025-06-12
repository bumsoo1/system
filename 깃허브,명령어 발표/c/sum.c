#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }

    unsigned long checksum = 0;
    unsigned long size = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        checksum += (unsigned char)ch;
        size++;
    }

    fclose(fp);

    unsigned long blocks = (size + 1023) / 1024;  // 1024바이트 블록 수 계산

    printf("%lu %lu %s\n", checksum, blocks, argv[1]);

    return 0;
}
