#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int main() {
    uid_t uid = getuid();
    gid_t gid = getgid();
    struct passwd *pw = getpwuid(uid);
    struct group *gr = getgrgid(gid);

    if (!pw || !gr) {
        perror("사용자/그룹 정보 조회 실패");
        return 1;
    }

    printf("uid=%d(%s) gid=%d(%s)\n", uid, pw->pw_name, gid, gr->gr_name);

    // 보조 그룹 조회
    int ngroups = 0;
    getgrouplist(pw->pw_name, gid, NULL, &ngroups);

    gid_t groups[ngroups];
    getgrouplist(pw->pw_name, gid, groups, &ngroups);

    printf("groups=");
    for (int i = 0; i < ngroups; i++) {
        struct group *g = getgrgid(groups[i]);
        if (g) {
            printf("%d(%s)", groups[i], g->gr_name);
        } else {
            printf("%d", groups[i]);
        }
        if (i != ngroups - 1)
            printf(",");
    }
    printf("\n");

    return 0;
}
