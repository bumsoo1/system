#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

int main() {
    DIR *proc_dir;
    struct dirent *entry;

    proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("/proc 디렉토리 열기 실패");
        return 1;
    }

    printf("PID\t프로세스 이름\n");
    printf("--------------------------\n");

    while ((entry = readdir(proc_dir)) != NULL) {
        // 디렉토리 이름이 숫자인 경우에만 (프로세스 디렉토리)
        if (isdigit(entry->d_name[0])) {
            char stat_path[256];
            snprintf(stat_path, sizeof(stat_path), "/proc/%s/stat", entry->d_name);

            FILE *stat_file = fopen(stat_path, "r");
            if (stat_file) {
                int pid;
                char comm[256];
                fscanf(stat_file, "%d (%[^)])", &pid, comm);
                printf("%d\t%s\n", pid, comm);
                fclose(stat_file);
            }
        }
    }

    closedir(proc_dir);
    return 0;
}
