#include <stdio.h>
#include <unistd.h>  // getlogin()

int main() {
    char *username = getlogin();
    if (username == NULL) {
        perror("getlogin 오류");
        return 1;
    }
    printf("%s\n", username);
    return 0;
}
