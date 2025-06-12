#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("stat 오류");
        return 1;
    }

    printf("파일: %s\n", argv[1]);
    printf("파일 크기: %ld 바이트\n", st.st_size);
    printf("블록 크기: %ld 바이트\n", st.st_blksize);
    printf("블록 수: %ld\n", st.st_blocks);
    printf("링크 수: %ld\n", st.st_nlink);
    printf("아이노드 번호: %ld\n", st.st_ino);

    printf("파일 권한: ");
    printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
    printf( (st.st_mode & S_IRUSR) ? "r" : "-");
    printf( (st.st_mode & S_IWUSR) ? "w" : "-");
    printf( (st.st_mode & S_IXUSR) ? "x" : "-");
    printf( (st.st_mode & S_IRGRP) ? "r" : "-");
    printf( (st.st_mode & S_IWGRP) ? "w" : "-");
    printf( (st.st_mode & S_IXGRP) ? "x" : "-");
    printf( (st.st_mode & S_IROTH) ? "r" : "-");
    printf( (st.st_mode & S_IWOTH) ? "w" : "-");
    printf( (st.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    printf("마지막 접근 시간: %s", ctime(&st.st_atime));
    printf("마지막 수정 시간: %s", ctime(&st.st_mtime));
    printf("상태 변경 시간: %s", ctime(&st.st_ctime));

    return 0;
}
