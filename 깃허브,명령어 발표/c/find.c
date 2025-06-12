#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void find(const char *path, const char *name) {
    DIR *d = opendir(path);
    if (!d) return;
    struct dirent *e;
    while ((e = readdir(d))) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;

        char p[1024];
        snprintf(p, sizeof(p), "%s/%s", path, e->d_name);

        if (!strcmp(e->d_name, name))
            printf("%s\n", p);

        struct stat st;
        if (!stat(p, &st) && S_ISDIR(st.st_mode))
            find(p, name);
    }
    closedir(d);
}

int main(int c, char **v) {
    if (c != 3) return 1;
    find(v[1], v[2]);
    return 0;
}
