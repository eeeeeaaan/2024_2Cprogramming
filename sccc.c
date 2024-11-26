#include <stdio.h>
#include <string.h>

int main(void) {
    char booklist[5][50] = {"Cygwin과 함께 배우는 C 프로그래밍",
                            "C 99",
                            "A book on C",
                            "C 프로그래밍",
                            "자바 프로그래밍"};

    printf("검색 문장을 입력하세요: ");
    char bookname[50];
    scanf("%s", bookname);
    for (int i = 0; i < 5; i++) {
        if (strstr(bookname, booklist[i]) != NULL) printf("%s\n", booklist[i]);
    }
}