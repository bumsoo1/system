#include <stdio.h>
#include <sys/statvfs.h>

int main() {
    struct statvfs stat;

    // 현재 디렉토리의 파일 시스템 정보 가져오기
    if (statvfs(".", &stat) != 0) {
        perror("statvfs 오류");
        return 1;
    }

    unsigned long total = stat.f_blocks * stat.f_frsize;
    unsigned long free  = stat.f_bfree  * stat.f_frsize;
    unsigned long avail = stat.f_bavail * stat.f_frsize;
    unsigned long used  = total - free;

    printf("파일시스템 정보 (현재 디렉토리 기준)\n");
    printf("전체 용량: %lu bytes\n", total);
    printf("사용 중:  %lu bytes\n", used);
    printf("사용 가능: %lu bytes\n", avail);

    return 0;
}
