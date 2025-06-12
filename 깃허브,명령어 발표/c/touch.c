#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <파일이름>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "a");  // append 모드: 없으면 생성, 있으면 열기
        if (fp == NULL) {
            perror("파일 생성 실패");
            continue;
        }
        fclose(fp);
    }

    return 0;
}
