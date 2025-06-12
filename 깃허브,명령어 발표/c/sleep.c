#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // sleep()

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <초>\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);
    if (seconds < 0) {
        fprintf(stderr, "양수 시간을 입력하세요.\n");
        return 1;
    }

    sleep(seconds);

    return 0;
}
