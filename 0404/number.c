#include <stdio.h>

void print_binary(unsigned char num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int count_ones(unsigned char num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

void print_high_4bits(unsigned char num) {
    unsigned char high = (num >> 4) & 0x0F; 
    for (int i = 3; i >= 0; i--) {
        printf("%d", (high >> i) & 1);
    }
}

int main() {
    int input;

    printf("0~255 사이의 정수를 입력하세요: ");
    scanf("%d", &input);

    if (input < 0 || input > 255) {
        printf("잘못된 입력입니다. 0부터 255 사이의 정수를 입력해주세요.\n");
        return 1;
    }

    unsigned char number = (unsigned char)input;

    printf("2진수: ");
    print_binary(number);
    printf("\n");

    int ones = count_ones(number);
    printf("1의 개수: %d\n", ones);

    printf("상위 4비트: ");
    print_high_4bits(number);
    printf("\n");

    return 0;
}
