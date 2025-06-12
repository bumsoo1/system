#include <stdio.h>
#include <stdlib.h>

#define HISTORY_FILE "history.txt"

int main() {
    FILE *fp = fopen(HISTORY_FILE, "r");
    if (!fp) {
        perror("history 파일 열기 실패");
        return 1;
    }

    char line[1024];
    int count = 1;
    while (fgets(line, sizeof(line), fp)) {
        printf("%5d  %s", count++, line);
    }

    fclose(fp);
    return 0;
}
