#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <검색어> <파일이름>\n", argv[0]);
        return 1;
    }

    char *keyword = argv[1];
    char *filename = argv[2];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, keyword) != NULL) {  // 문자열 포함 여부 검사
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
