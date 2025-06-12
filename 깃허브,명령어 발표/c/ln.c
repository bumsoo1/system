#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <기존파일> <새링크>\n", argv[0]);
        return 1;
    }

    if (link(argv[1], argv[2]) != 0) {
        perror("링크 생성 실패");
        return 1;
    }

    printf("하드링크 %s → %s 생성 완료\n", argv[2], argv[1]);

    return 0;
}
