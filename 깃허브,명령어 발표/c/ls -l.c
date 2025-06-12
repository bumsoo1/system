#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

void print_permissions(mode_t mode) {
    char perms[11] = "----------";

    if (S_ISDIR(mode)) perms[0] = 'd';
    else if (S_ISLNK(mode)) perms[0] = 'l';
    else if (S_ISCHR(mode)) perms[0] = 'c';
    else if (S_ISBLK(mode)) perms[0] = 'b';

    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';

    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';

    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';

    printf("%s ", perms);
}

int main(int argc, char *argv[]) {
    const char *dir_path = ".";  // 기본 현재 디렉토리
    if (argc > 1) dir_path = argv[1];

    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("디렉토리 열기 실패");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dir_path, entry->d_name);

        struct stat st;
        if (lstat(fullpath, &st) == -1) {
            perror("stat 실패");
            continue;
        }

        print_permissions(st.st_mode);
        printf("%2lu ", (unsigned long)st.st_nlink);

        struct passwd *pw = getpwuid(st.st_uid);
        struct group *gr = getgrgid(st.st_gid);

        printf("%-8s %-8s ", pw ? pw->pw_name : "?", gr ? gr->gr_name : "?");
        printf("%8lld ", (long long)st.st_size);

        char timebuf[64];
        struct tm *tm = localtime(&st.st_mtime);
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);
        printf("%s ", timebuf);

        printf("%s", entry->d_name);

        // 심볼릭 링크면 -> 링크 타겟도 출력
        if (S_ISLNK(st.st_mode)) {
            char linktarget[1024];
            ssize_t len = readlink(fullpath, linktarget, sizeof(linktarget)-1);
            if (len != -1) {
                linktarget[len] = '\0';
                printf(" -> %s", linktarget);
            }
        }

        printf("\n");
    }

    closedir(dir);
    return 0;
}
