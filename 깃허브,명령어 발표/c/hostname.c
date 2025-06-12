#include <stdio.h>
#include <unistd.h>

#define MAX_HOSTNAME_LEN 256

int main() {
    char hostname[MAX_HOSTNAME_LEN];

    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname 실패");
        return 1;
    }

    printf("%s\n", hostname);
    return 0;
}
