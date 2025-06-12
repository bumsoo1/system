#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DEFAULT_LINES 10

int main(int argc, char *argv[]) {
    int lines_to_print = DEFAULT_LINES;
    const char *filename;

    // 인자 처리: ./head [lines] filename 또는 ./head filename
    if (argc == 3) {
        lines_to_print = atoi(argv[1]);
        if (lines_to_print <= 0) {
            fprintf(stderr, "유효하지 않은 줄 수: %s\n", argv[1]);
            return 1;
        }
        filename = argv[2];
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        fprintf(stderr, "사용법: %s [출력할_줄수] <파일 이름>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "파일 열기 오류: %s\n", strerror(errno));
        return 1;
    }

    char buffer[1024];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), fp) && count < lines_to_print) {
        fputs(buffer, stdout);
        count++;
    }

    fclose(fp);
    return 0;
}
