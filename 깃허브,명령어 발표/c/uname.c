#include <stdio.h>
#include <sys/utsname.h>  // uname 구조체 및 함수

int main() {
    struct utsname sysinfo;

    if (uname(&sysinfo) == -1) {
        perror("uname 오류");
        return 1;
    }

    printf("시스템 이름: %s\n", sysinfo.sysname);
    printf("노드 이름: %s\n", sysinfo.nodename);
    printf("릴리즈: %s\n", sysinfo.release);
    printf("버전: %s\n", sysinfo.version);
    printf("머신: %s\n", sysinfo.machine);

    return 0;
}
