#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <PID>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);

    if (kill(pid, SIGKILL) == -1) {
        perror("프로세스 종료 실패");
        return 1;
    }

    printf("PID %d 프로세스가 종료되었습니다.\n", pid);
    return 0;
}
