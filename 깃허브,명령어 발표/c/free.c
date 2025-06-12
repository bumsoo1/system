#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("meminfo 열기 실패");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // MemTotal, MemFree, MemAvailable, Buffers, Cached 등만 출력
        if (strncmp(line, "MemTotal:", 9) == 0 ||
            strncmp(line, "MemFree:", 8) == 0 ||
            strncmp(line, "MemAvailable:", 13) == 0 ||
            strncmp(line, "Buffers:", 8) == 0 ||
            strncmp(line, "Cached:", 7) == 0) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
