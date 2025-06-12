#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <명령어> [인자...]\n", argv[0]);
        return 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork 실패");
        return 1;
    }

    if (pid == 0) {
        // 자식 프로세스: 명령어 실행
        execvp(argv[1], &argv[1]);
        perror("exec 실패");
        exit(1);
    } else {
        // 부모 프로세스: 자식 대기
        int status;
        waitpid(pid, &status, 0);

        gettimeofday(&end, NULL);

        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

        printf("실행 시간: %.6f초\n", elapsed);

        return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }
}
