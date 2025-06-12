#include <stdio.h>
#include <ctype.h>

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

    int lines = 0, words = 0, bytes = 0;
    int in_word = 0;
    int c;

    while ((c = fgetc(fp)) != EOF) {
        bytes++;

        if (c == '\n')
            lines++;

        if (isspace(c))
            in_word = 0;
        else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    fclose(fp);

    printf("%d %d %d %s\n", lines, words, bytes, argv[1]);

    return 0;
}
