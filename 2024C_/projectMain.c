#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct {
    char english[15];
    char korean[30]; // 포인터 배열, 3개 뜻(문자열) 가리키는 포인터
} words;

void input(int, words *wordList);

int randomSelect(FILE *, words *, int *ran);

int main() {
    words word[30];
    int file = 1;
    input(file, word);
    //종료 확인하는 변수
    _Bool Finish = 0;

    while (!Finish) {

        printf(">> 영어 단어 암기 프로그램 <<\n");
        printf("1. 영어 단어 맞추기    2. 플래쉬카드\n");
        printf("3. 행맨(hangman)     4. 단어장 관리\n");
        printf("5. 프로그램 종료\n");

        int num;
        printf("번호를 선택하세요: ");
        scanf("%d", &num);

        //1. 영어 단어 맞추기
        if (num == 1) {
            words words[30];

            int randint = 0;


            int filenumber, outputForm;
            printf("파일명(일자) :");
            scanf("%d", &filenumber);

            printf("출력 방식(알파벳 순서대로 : 1, 무작위 :2) : ");
            scanf("%d", &outputForm);

            // 여기서 word에 n.dic에 해당하는 단어가 담겼음
            input(filenumber, words);

            _Bool isFinish = 0;
            do {
                char add[] = "2024C_/";
                char filenum[2];
                itoa(filenumber, filenum, 10); // filenumber 숫자로 바꾸기

                // 경로 합치기
                strcat(add, filenum); //ex . 2024C_/1
                strcat(add, ".dic"); // ex. 2024C_/1.dic

                FILE *dict_Ptr = fopen(add, "r");


                char *answer = malloc(30 * sizeof(char));
                randomSelect(dict_Ptr, words, &randint);
                // 무작위로 영단어 출력 및 인덱스 반환
                scanf("%s", answer);
                if (strcmp(answer, ".quit") == 0) isFinish = 1;
                else {
                    //정답확인
                    if (strcmp(words[randint].english, answer) == 0) {
                        printf("success\n");
                        //점수 관련 조치
                    } else {
                        printf("fail\n");
                    }
                }

                fclose(dict_Ptr);
            } while (!isFinish);


        }

            //2. 플래쉬 카드
        else if (num == 2) {

        }

            //3. 행맨(hangman)
        else if (num == 3) {

        }

            // 4. 단어장 관리
        else if (num == 4) {

        }

            //5. 프로그램 종료
        else if (num == 5) {
            Finish = 1;
        }
            // 예외처리
        else {
            printf("유효하지 않은 숫자입니다. \n");
        }
    }

}

// 랜덤으로 추출하기

int randomSelect(FILE *fp, words *wordList, int *ran) {
    int random = rand() % 30;
    printf("%s  :", wordList[random].korean);
    *ran = random;
    return *ran;
}


// 알파벳 순으로 추출하기




// dic.list 에서 n.dic 접근하기
// 그리고 구조체에 해당 영/한 조합 데이터 만들어주기

void input(int filenumber, words *wordList) {
    char whatDictionary[100]; // dic.list의 요소를 가리키는 파일 포인터 ( 즉 1.dic, 2.dic 등등 )

    FILE *dic; // dic.list를 열기 위한 파일 포인터


    // 여기 상대 경로 복사해서 넣어줘야하는 듯 합니다..?ㅠㅠ
    dic = fopen("2024C_/dic.list", "r");
    if (dic == NULL) {
        printf("dic.list 가 비어있습니다.");
    }

    for (int i = 0; i < filenumber; i++) {
        fscanf(dic, "%s", whatDictionary);
    }


    printf("%s\n", whatDictionary);
    char add[] = "2024C_/";
    // 경로 합치기
    strcat(add, whatDictionary);
    printf("%s\n", add);
    fclose(dic);

    // 아까 합쳐놨던 주소의 n.dic로 접근하기
    FILE *dd = fopen(add, "r");


    char eng[15];
    char kor[50];

    for (int i = 0; i < 30; i++) {
        fscanf(dd, "%[^,], %[^\n]\n", eng, kor);
        strcpy(wordList[i].english, eng);
        strcpy(wordList[i].korean, kor);
    }

    //디버깅: 제대로 출력됨
//    for (int i = 0; i < 30; i++) {
//        printf("%s %s\n", wordList[i].english, wordList[i].korean);
//    }
    fclose(dd);

}