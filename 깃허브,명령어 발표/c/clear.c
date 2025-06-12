#include <stdio.h>

int main() {
    // ANSI escape code로 터미널 화면 지우기
    printf("\033[2J");   // 화면 전체 지우기
    printf("\033[H");    // 커서를 좌측 상단(1,1) 위치로 이동
    fflush(stdout);      // 출력 버퍼 비우기
    return 0;
}
