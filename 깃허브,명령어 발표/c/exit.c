#include <stdio.h>
#include <stdlib.h>  // exit 함수

int main(int argc, char *argv[]) {
    int status = 0;  // 기본 종료 상태

    if (argc > 1) {
        status = atoi(argv[1]);  // 인자가 있으면 종료 상태로 변환
    }

    printf("프로그램을 종료합니다. 종료 상태: %d\n", status);
    exit(status);  // 프로세스 종료
}
