#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    struct utmp *ut;

    setutent();  // utmp 파일 처음으로 이동

    while ((ut = getutent()) != NULL) {
        if (ut->ut_type == USER_PROCESS) {  // 실제 로그인 사용자만 출력
            printf("%s\t%s\t%s\n", ut->ut_user, ut->ut_line, ut->ut_host);
        }
    }

    endutent();  // utmp 파일 닫기
    return 0;
}
