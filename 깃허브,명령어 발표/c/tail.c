#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_LINES 10
#define MAX_LINES 10000   // 최대 저장 가능한 줄 수 (조절 가능)

int main(int argc, char *argv[]) {
    int lines_to_print = DEFAULT_LINES;
    const char *filename;

    // 인자 처리: ./tail [lines] filename 또는 ./tail filename
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

    char *lines[MAX_LINES];
    int count = 0;
    size_t len = 0;

    // 파일에서 줄을 읽어 배열에 저장 (최대 MAX_LINES)
    while (count < MAX_LINES && getline(&lines[count], &len, fp) != -1) {
        count++;
        len = 0;
    }

    fclose(fp);

    // 출력 시작 줄 계산
    int start = count - lines_to_print;
    if (start < 0) start = 0;

    for (int i = start; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    return 0;
}
