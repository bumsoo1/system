#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char type(mode_t mode);
char *perm(mode_t mode);
void printStat(char *pathname, char *file, struct stat *st);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct dirent *d;
    struct stat st;
    char path[BUFSIZ + 1];

    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name); 

        if (lstat(path, &st) < 0) { 
            perror(path);
            continue;
        }

        printStat(path, d->d_name, &st); 
        putchar('\n');
    }

    closedir(dp); 
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st) {
    printf("%5ld ", st->st_blocks);                                
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));         
    printf("%3ld ", (long)st->st_nlink);                             
    printf("%s %s ", getpwuid(st->st_uid)->pw_name,                 
                   getgrgid(st->st_gid)->gr_name);                 
    printf("%9ld ", (long)st->st_size);                              
    printf("%.12s ", ctime(&st->st_mtime) + 4);                     
    printf("%s", file);                                             
}

char type(mode_t mode) {
    if (S_ISREG(mode)) return '-';  
    if (S_ISDIR(mode)) return 'd';   
    if (S_ISCHR(mode)) return 'c';   
    if (S_ISBLK(mode)) return 'b';   
    if (S_ISLNK(mode)) return 'l';   
    if (S_ISFIFO(mode)) return 'p';  
    if (S_ISSOCK(mode)) return 's';  
    return '?';                      
}

char* perm(mode_t mode) {
    static char perms[10];
    int i;

    for (i = 0; i < 9; i++)
        perms[i] = '-';
    perms[9] = '\0';

    if (mode & S_IRUSR) perms[0] = 'r';
    if (mode & S_IWUSR) perms[1] = 'w';
    if (mode & S_IXUSR) perms[2] = 'x';
    if (mode & S_IRGRP) perms[3] = 'r';
    if (mode & S_IWGRP) perms[4] = 'w';
    if (mode & S_IXGRP) perms[5] = 'x';
    if (mode & S_IROTH) perms[6] = 'r';
    if (mode & S_IWOTH) perms[7] = 'w';
    if (mode & S_IXOTH) perms[8] = 'x';

    return perms;
}
