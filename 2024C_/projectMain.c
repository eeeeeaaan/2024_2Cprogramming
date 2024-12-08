#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <synchapi.h>


typedef struct {
    char english[15];
    char korean[3][30]; // 포인터 배열, 3개 뜻(문자열) 가리키는 포인터
} words;

void input(int, words *wordList, int *);
void sortStruct(words *wordList, int*);
int randomSelect( words *, int *ran);
int countLine(const char*);
//2. flash card
void randomFlash(words *, int *ran, int speed);

// 4. 단어장 관리
void addWord(int);
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

            int filenumber, outputForm, countLine=0;
            printf("파일명(일자) :");
            scanf("%d", &filenumber);

            printf("출력 방식(알파벳 순서대로 : 1, 무작위 :2) : ");
            scanf("%d", &outputForm);

            // 여기서 word에 n.dic에 해당하는 단어가 담겼음
            input(filenumber, words, &countLine);
            _Bool isFinish = 0;
            int rightProblem  =0 , allProblem=0 ;

            if(outputForm ==1){ // 알파벳 정렬
                double score ;

                sortStruct(words, &countLine); // 정렬 후 꺼내오기만 하면됨.
                int index=-1;
                do{
                    index++;

                    char *answer = malloc(30 * sizeof(char));
                    printf("%s -> ",words[index].korean[0]);

                    scanf("%s", answer);
                    if (strcmp(answer, ".quit") == 0) {

                        score = (double)rightProblem/ allProblem;
                        printf("%.2lf\n", 100*score);
                        isFinish = 1;
                    }
                    else{
                        if(strcmp(words[index].english, answer)==0){
                            printf("success\n");
                            rightProblem++ ;
                            allProblem++;
                        }else{
                            printf("fail\n");
                            allProblem++;
                        }
                    }
                } while (!isFinish);
            }else if(outputForm==2){ //무작위 정렬
                double score;
                int randint = 0;
                do {
                    char *answer = malloc(30 * sizeof(char));
                    randomSelect(words, &randint);
                    // 무작위로 영단어 출력 및 인덱스 반환
                    scanf("%s", answer);
                    if (strcmp(answer, ".quit") == 0) {
                        score = (double)rightProblem/ allProblem;
                        printf("%.2lf\n", 100*score);
                        isFinish = 1;
                    }
                    else {
                        //정답확인
                        if (strcmp(words[randint].english, answer) == 0) {
                            printf("success\n");
                            rightProblem ++;
                            allProblem++;
                            //점수 관련 조치
                        } else {
                            printf("fail\n");
                            allProblem++;
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
            int speed, filenumber, outputForm, randint=0, countLine=0;
            printf("속도(초) :");
            scanf("%d", &speed);
            printf("파일명(일자) :");
            scanf("%d", &filenumber);

            printf("출력방식(알파벳 순서대로: 1, 무작위 :2) :");
            scanf("%d", &outputForm);
            // 구조체에 담기
            input(filenumber, word, &countLine);

            if(outputForm==1){
                sortStruct(word, &countLine);
                for (int i =0 ;i<30; i++){
                    printf("%s\n", word[i].english);
                    Sleep(speed*1000);

                    printf("%s\n", word[i].korean[0]);
                    Sleep(speed*1000);



                }
            }else if (outputForm==2){
                for (int i =0 ;i<30; i++){
                    randomFlash(word, &randint, speed );

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
            // 단어장 관리 메뉴로.. 라는게 무슨 소리인가?
            _Bool toMainWordList =0;
            while(!toMainWordList){
                system("cls"); // linux 에서는 새롭게 바꿔줘야함
                Sleep(300);
                printf("1. 새 파일 추가하기     2. 새 단어 추가하기\n");
                printf("3. 단어장 보기         4. 단어 파일 목록 보기\n");
                printf("5. 단어장 관리 종료\n");


                int num, countLine=0 ;
                printf("번호를 입력하세요 :");
                scanf("%d", &num);



                //입력 버퍼 비우기...
                int c ;
                while((c= getchar())!='\n' && c != EOF);

                if(num==1){

                    char n ;
                    int count=0;

                    // 현재 dic 수 세기 ( 개행 \n 사용해서 ) 여기 리눅스 루트 고쳐줘야함
                    FILE *fileList = fopen("2024C_/dic.list", "r");
                    while(fscanf(fileList, "%c",&n) != EOF){
                        if(n == '\n'){
                            count++;
                        }
                    }
                    fclose(fileList);


                    // dic.list에 추가하기
                    FILE *writeList = fopen("2024C_/dic.list", "a");

                    fprintf(writeList, "\n%d.dic",count+2);
                    fclose(writeList);

                    // 단어 추가하기
                    addWord(count+2);


                }
                else if (num==2){
                    printf("파일명(일자) :");
                    int day ;
                    scanf("%d", &day);
                    addWord(day);

                }
                else if(num==3){
                    printf("파일명(일자) :");
                    int days;
                    words word[30] ;
                    scanf("%d", &days);
                    input(days, word,&countLine );
                    printf("-----단어장---------\n");
                    for(int i =0 ;i<countLine; i++){
                        printf("%s ", word[i].english);
                        printf("%s\n", word[i].korean[0]);

                    }
                    printf("\n");

                }
                else if(num==4){
                    printf("-------단어 파일 목록-----------");
                    FILE *fp = fopen("2024C_/dic.list", "r");

                }
                else{
                    toMainWordList=1;
                }
            }

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
    *ran = random;
    printf("%s  ->", wordList[random].korean[0]);
    return *ran;
}


// 랜덤으로 추출하고 영어, 한글 n초 간격으로 출력하주기
void randomFlash (words *wordList, int *ran, int speed){
    int random = rand() %30 ;
    printf("%s\n", wordList[random].english);
    Sleep(speed*1000);

    printf("%s\n", wordList[random].korean[0]);

}

// 알파벳 순으로 정렬하기
void sortStruct( words *wordList,int *countLine){
    words tem;
    for (int i=0 ; i<*countLine;i++){
        for ( int j=i+1 ; j<*countLine ;j++){
            if(strcmp(wordList[i].english, wordList[j].english)>0){
                tem =wordList[i];
                wordList[i] = wordList[j];
                wordList[j] = tem;
            }
        }
    }
//    printf("=== DEBUG: 정렬된 단어 목록 ===\n");
//    for (int i = 0; i < *countLine; i++) {
//        printf("english = %s, korean[0] = %s\n",
//               wordList[i].english, wordList[i].korean[0]);
//    }
//    printf("================================\n");
}


int countLine(const char *filename){
    FILE * file= fopen(filename, "r");
    int count =0 ;
    char c;
    while ((c= fgetc(file)) != EOF){
        if(c=='\n'){
            count++;
        }
    }
    fclose(file);
    count +=1;
    printf("countLine : %d",count);
    return count ;
}


// dic.list 에서 n.dic 접근하기
// 그리고 구조체에 해당 영/한 조합 데이터 만들어주기
void input(int filenumber, words *wordList, int *wordCount) {
    char whatDictionary[100]; // 파일명 저장용
    FILE *dic = fopen("2024C_/dic.list", "r");

    // 리눅스에서는 이렇게
    // FILE *dic = fopen("dic.list", "r");
    if (!dic) {
        printf("dic.list 파일을 열 수 없습니다.\n");
        return;
    }

    // n번째 파일 이름 가져오기
    for (int i = 0; i < filenumber; i++) {
        if (fscanf(dic, "%s", whatDictionary) == EOF) {
            printf("dic.list 파일에서 데이터를 읽는 중 문제가 발생했습니다.\n");
            fclose(dic);
            return;
        }
    }
    fclose(dic);


    // clion 버전
    // 경로 생성
    char add[150] = "2024C_/";
    strcat(add, whatDictionary);
    // 리눅스에서는 위 두줄 없애고 그냥 아래 countLine 안에 add 말고 whatDictionary 넣으면 됨
    // 단어 수 계산
    *wordCount = countLine(add);
    if (*wordCount == 0) {
        printf("파일에 단어가 없습니다.\n");
        return;
    }

    FILE *dd = fopen(add, "r");
    if (!dd) {
        printf("%s 파일을 열 수 없습니다.\n", add);
        return;
    }
    //


    char eng[15];
    char kor1[30], kor2[30], kor3[30];
    int count = 0;

    while (count < *wordCount) {
        // 각 줄에서 최대 3개의 뜻을 읽음
        int readNumber = fscanf(dd, " %[^,\n], %[^,\n]", eng, kor1);
        if (readNumber < 2) break; // 데이터가 부족하면 종료

        // 구조체 초기화
        strcpy(wordList[count].english, eng);
        strcpy(wordList[count].korean[0], kor1);

        // 두 번째 뜻이 있으면 읽기
        if (fgetc(dd) == ',') {
            fscanf(dd, "%[^,\n]", kor2);
            strcpy(wordList[count].korean[1], kor2);
        } else {
            wordList[count].korean[1][0] = '\0'; // 빈 문자열 처리
        }

        // 세 번째 뜻이 있으면 읽기
        if (fgetc(dd) == ',') {
            fscanf(dd, "%[^,\n]", kor3);
            strcpy(wordList[count].korean[2], kor3);
        } else {
            wordList[count].korean[2][0] = '\0'; // 빈 문자열 처리
        }

        count++;
    }
    fclose(dd);

    printf("=== DEBUG: 구조체에 저장된 단어 목록 ===\n");
    for (int i = 0; i < count; i++) {
        printf("english = %s, korean[0] = %s, korean[1] = %s, korean[2] = %s\n",
               wordList[i].english,
               wordList[i].korean[0],
               wordList[i].korean[1],
               wordList[i].korean[2]);
    }
    printf("======================================\n");
}


void addWord(int day){
    // 리눅스에서는 ndic의 address 대신 file add 가 들어가야한단다.
    char address[50]="2024C_/";
    char fileadd[20] ;


    sprintf(fileadd, "%d.dic", day);
    strcat(address, fileadd);


    FILE *ndic = fopen(address, "a");

    _Bool isFinish =0 ;
    int word_count =0 ;
    char word_mean[50], english[50], korean[50];

    while(!isFinish){
        //입력받기...
        fscanf(stdin, " %[^\n]", word_mean);
        int c;
        while((c= getchar()) != '\n' && c != EOF);

        if (strcmp(word_mean, ".add")==0 ){
            isFinish=1;
        }
        else if(word_count==20){
            isFinish =1;
        }
        else{
            sscanf(word_mean, "%s %[^\n]", english, korean);
            fprintf(ndic, "%s, %s\n", english, korean);
            word_count ++;
        }
    }

    fclose(ndic);
}