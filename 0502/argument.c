#include <stdio.h>

int main(int argc, char *argv[]) {

    printf("인자의 개수: %d\n", argc);
    printf("전달된 인자들:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}