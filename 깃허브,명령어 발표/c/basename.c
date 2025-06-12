#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <경로>\n", argv[0]);
        return 1;
    }

    char *path = argv[1];
    char *base = strrchr(path, '/');  // 마지막 '/' 위치 찾기

    if (base != NULL) {
        base++;  // '/' 다음 문자부터가 파일명
        if (*base == '\0') {
            // 경로가 '/'로 끝난 경우, 마지막 '/' 이전 문자열 출력
            // 예: "/usr/local/bin/"
            // 이런 경우 간단히 '/'를 제거하고 재탐색하는 방식도 있음
            // 여기서는 그냥 '/' 출력
            base = "/";
        }
    } else {
        base = path;  // '/' 없으면 전체가 파일명
    }

    printf("%s\n", base);
    return 0;
}
