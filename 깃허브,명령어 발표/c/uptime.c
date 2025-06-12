#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (fp == NULL) {
        perror("/proc/uptime 열기 실패");
        return 1;
    }

    double uptime_seconds;
    if (fscanf(fp, "%lf", &uptime_seconds) != 1) {
        fprintf(stderr, "uptime 정보 읽기 실패\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    int days = uptime_seconds / (60 * 60 * 24);
    int hours = ((int)uptime_seconds % (60 * 60 * 24)) / (60 * 60);
    int minutes = ((int)uptime_seconds % (60 * 60)) / 60;
    int seconds = (int)uptime_seconds % 60;

    printf("시스템 가동 시간: %d일 %d시간 %d분 %d초\n",
           days, hours, minutes, seconds);

    return 0;
}
