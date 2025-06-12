#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <출력파일>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "w");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }

    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);       // 표준 출력으로 출력
        fputc(c, fp);     // 파일에도 쓰기
    }

    fclose(fp);
    return 0;
}
