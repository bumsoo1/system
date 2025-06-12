#include <stdio.h>
#include <time.h>

int main() {
    time_t now = time(NULL);  // 현재 시간 가져오기
    if (now == (time_t)(-1)) {
        perror("time 오류");
        return 1;
    }

    struct tm *local = localtime(&now);  // 지역 시간으로 변환
    if (local == NULL) {
        perror("localtime 오류");
        return 1;
    }

    // 날짜 및 시간 출력 형식: YYYY-MM-DD HH:MM:SS
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",
           local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
           local->tm_hour, local->tm_min, local->tm_sec);

    return 0;
}
