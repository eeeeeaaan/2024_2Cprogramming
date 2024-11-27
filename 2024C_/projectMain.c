#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <synchapi.h>


typedef struct {
    char english[15];
    char korean[30]; // 포인터 배열, 3개 뜻(문자열) 가리키는 포인터
} words;

void input(int, words *wordList);
void sortStruct(words *wordList);
int randomSelect( words *, int *ran);

//2. flash card
void randomFlash(words *, int *ran, int speed);
int main() {
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




            int filenumber, outputForm;
            printf("파일명(일자) :");
            scanf("%d", &filenumber);

            printf("출력 방식(알파벳 순서대로 : 1, 무작위 :2) : ");
            scanf("%d", &outputForm);

            // 여기서 word에 n.dic에 해당하는 단어가 담겼음
            input(filenumber, words);
            _Bool isFinish = 0;

            if(outputForm ==1){ // 알파벳 정렬
                sortStruct(words); // 정렬 후 꺼내오기만 하면됨.
                int index=-1;
                do{
                    index++;

                    char *answer = malloc(30 * sizeof(char));
                    printf("%s",words[index].korean);

                    scanf("%s", answer);
                    if (strcmp(answer, ".quit") == 0) isFinish = 1;
                    else{
                        if(strcmp(words[index].english, answer)==0){
                            printf("success\n");
                        }else{
                            printf("fail\n");
                        }
                    }
                } while (!isFinish);
            }else if(outputForm==2){ //무작위 정렬
                int randint = 0;
                do {
                    char *answer = malloc(30 * sizeof(char));
                    randomSelect(words, &randint);
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


                } while (!isFinish);
            }else{
                printf("유효하지 않은 번호입니다.");
            }




        }

            //2. 플래쉬 카드
        else if (num == 2) {
            words word[30];
            int speed, filenumber, outputForm, randint=0;
            printf("속도(초) :");
            scanf("%d", &speed);
            printf("파일명(일자) :");
            scanf("%d", &filenumber);

            printf("출력방식(알파벳 순서대로: 1, 무작위 :2) :");
            scanf("%d", &outputForm);
            // 구조체에 담기
            input(filenumber, word);

            if(outputForm==1){
                sortStruct(word);
                for (int i =0 ;i<30; i++){
                    printf("%s\n", word[i].english);
                    Sleep(speed*1000);
                    printf("%s\n", word[i].korean);
                    Sleep(speed*1000);
                }
            }else if (outputForm==2){
                for (int i =0 ;i<30; i++){
                    randomFlash(word, &randint, speed );
                    Sleep(speed*1000);
                }

            }else{
                printf("유효하지 않은 출력방식 입니다. ");
            }

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

// 랜덤으로 추출하고 한글단어 제시해주기 (1)
int randomSelect(words *wordList, int *ran) {
    int random = rand() % 30;
    printf("%s  :", wordList[random].korean);
    *ran = random;
    return *ran;
}


// 랜덤으로 추출하고 영어, 한글 n초 간격으로 출력하주기
void randomFlash (words *wordList, int *ran, int speed){
    int random = rand() %30 ;
    printf("%s\n", wordList[random].english);
    Sleep(speed *1000);
    printf("%s\n", wordList[random].korean);
}

// 알파벳 순으로 정렬하기
void sortStruct( words *wordList){
    words tem;
    for (int i=0 ; i<30 ;i++){
        for ( int j=0 ; j<i ;j++){
            if(strcmp(wordList[i].english, wordList[j].english) ==-1){
                tem =wordList[i];
                wordList[i] = wordList[j];
                wordList[j] = tem;
            }
        }
    }
}



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

    char add[] = "2024C_/";
    // 경로 합치기
    strcat(add, whatDictionary);

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