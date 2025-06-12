#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10000
#define MAX_LEN 1024

// qsort용 비교 함수 (문자열 사전 순)
int cmp(const void *a, const void *b) {
    const char * const *pa = a;
    const char * const *pb = b;
    return strcmp(*pa, *pb);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <파일이름>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }

    char *lines[MAX_LINES];
    int count = 0;
    char buffer[MAX_LEN];

    while (fgets(buffer, sizeof(buffer), fp) && count < MAX_LINES) {
        // 줄 끝 개행 문자 제거
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        lines[count] = malloc(len);
        if (!lines[count]) {
            perror("메모리 할당 실패");
            fclose(fp);
            return 1;
        }
        strcpy(lines[count], buffer);
        count++;
    }

    fclose(fp);

    qsort(lines, count, sizeof(char *), cmp);

    for (int i = 0; i < count; i++) {
        printf("%s\n", lines[i]);
        free(lines[i]);
    }

    return 0;
}
