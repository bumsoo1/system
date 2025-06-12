#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <파일1> <파일2>\n", argv[0]);
        return 1;
    }

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");

    if (!fp1 || !fp2) {
        perror("파일 열기 실패");
        return 1;
    }

    char line1[MAX_LINE], line2[MAX_LINE];
    int lineno = 1;

    while (1) {
        char *res1 = fgets(line1, sizeof(line1), fp1);
        char *res2 = fgets(line2, sizeof(line2), fp2);

        if (!res1 && !res2) break; // 둘 다 끝났으면 종료

        // 줄바꿈 문자 제거
        if (res1) line1[strcspn(line1, "\n")] = '\0';
        if (res2) line2[strcspn(line2, "\n")] = '\0';

        if (!res1) {
            printf("%s: EOF\n", argv[1]);
            printf("%d: %s\n", lineno, line2);
        } else if (!res2) {
            printf("%s: EOF\n", argv[2]);
            printf("%d: %s\n", lineno, line1);
        } else if (strcmp(line1, line2) != 0) {
            printf("%d:\n", lineno);
            printf("< %s\n", line1);
            printf("> %s\n", line2);
        }

        lineno++;
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
