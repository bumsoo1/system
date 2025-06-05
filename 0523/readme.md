
 📘 프로세스 생성 예시
 부모 프로세스가 자식 프로세스를 생성하는 방법

#include <stdio.h>      // 표준 입출력
#include <unistd.h>     // fork 함수 사용을 위해 필요
#include <sys/types.h>  // pid_t 자료형을 위해 필요

int main() {
    pid_t pid;  // 프로세스 ID를 저장할 변수

     🔧 fork() 시스템 호출
     부모 프로세스를 복제하여 새로운 자식 프로세스를 생성
    pid = fork();

     ⚠️ fork() 호출 실패 시
    if (pid < 0) {
        perror("fork 실패");
        return 1;
    }

     ✅ 자식 프로세스일 경우 (pid == 0)
    else if (pid == 0) {
        printf("🔹 자식 프로세스입니다. PID: %d\n", getpid());
        printf("   부모 PID: %d\n", getppid());
    }

     ✅ 부모 프로세스일 경우 (pid > 0)
    else {
        printf("🔸 부모 프로세스입니다. 자식 PID: %d\n", pid);
        printf("   부모 본인의 PID: %d\n", getpid());
    }

    return 0;
}
