#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
    char english[15];
    char korean[3][30]; // 포인터 배열, 3개 뜻(문자열) 가리키는 포인터
} words;
void input(int, words *, int *);
int countLine(const char * filename);
void sortStruct(words*, int);
int main() {
    int filenumber =1;
    printf("%d",countLine("2024C_/dic.list"));

}
void sortStruct(words *wordList, int wordCount) {
    words temp; // 임시 구조체 변수
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            // 빈 데이터 무시
            if (wordList[i].english[0] == '\0' || wordList[j].english[0] == '\0') continue;

            // 사전순 비교
            if (strcmp(wordList[i].english, wordList[j].english) > 0) {
                temp = wordList[i];
                wordList[i] = wordList[j];
                wordList[j] = temp;
            }
        }
    }

    // 정렬 결과 디버깅 출력
    printf("=== DEBUG: 정렬된 단어 목록 ===\n");
    for (int i = 0; i < wordCount; i++) {
        if (wordList[i].english[0] != '\0') { // 빈 데이터 무시
            printf("english = %s, korean[0] = %s\n",
                   wordList[i].english, wordList[i].korean[0]);
        }
    }
    printf("================================\n");
}
void input(int filenumber, words *wordList, int *wordCount) {
    char whatDictionary[100]; // 파일명 저장용
    FILE *dic = fopen("2024C_/dic.list", "r");
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

    // 경로 생성
    char add[150] = "2024C_/";
    strcat(add, whatDictionary);

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

    char eng[15];
    char kor1[30], kor2[30], kor3[30];
    int count = 0;

    while (count < *wordCount) {
        // 각 줄에서 최대 3개의 뜻을 읽음
        int readNumber = fscanf(dd, "%[^,], %[^,], %[^,], %[^\n]",
                                eng, kor1, kor2, kor3);
        if (readNumber >= 2) { // 최소 영어와 뜻 1개는 읽혀야 함
            strcpy(wordList[count].english, eng);
            strcpy(wordList[count].korean[0], kor1);
            if (readNumber >= 3)
                strcpy(wordList[count].korean[1], kor2);
            else
                wordList[count].korean[1][0] = '\0'; // 초기화
            if (readNumber == 4)
                strcpy(wordList[count].korean[2], kor3);
            else
                wordList[count].korean[2][0] = '\0'; // 초기화
        } else {
            // 빈 데이터 처리
            strcpy(wordList[count].english, "\0");
            strcpy(wordList[count].korean[0], "\0");
            wordList[count].korean[1][0] = '\0';
            wordList[count].korean[2][0] = '\0';
        }
        count++;
    }
    fclose(dd);

    // 디버깅 출력
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

//void input(int filenumber, words *wordList, int *wordCount) {
//    char whatDictionary[100]; // 파일명 저장용
//    FILE *dic = fopen("2024C_/dic.list", "r");
//    if (!dic) {
//        printf("dic.list 파일을 열 수 없습니다.\n");
//        return;
//    }
//
//    // n번째 파일 이름 가져오기
//    for (int i = 0; i < filenumber; i++) {
//        if (fscanf(dic, "%s", whatDictionary) == EOF) {
//            printf("dic.list 파일에서 데이터를 읽는 중 문제가 발생했습니다.\n");
//            fclose(dic);
//            return;
//        }
//    }
//    fclose(dic);
//
//    // 경로 생성
//    char add[150] = "2024C_/";
//    strcat(add, whatDictionary);
//
//    // 단어 수 계산
//    *wordCount = countLine(add);
//    if (*wordCount == 0) {
//        printf("파일에 단어가 없습니다.\n");
//        return;
//    }
//
//    FILE *dd = fopen(add, "r");
//    if (!dd) {
//        printf("%s 파일을 열 수 없습니다.\n", add);
//        return;
//    }
//
//    char eng[15];
//    char kor1[30], kor2[30], kor3[30];
//    int count = 0;
//
//    while (!feof(dd) && count < *wordCount) {
//        // 각 줄에서 최대 3개의 뜻을 읽음
//        int readNumber = fscanf(dd, "%[^,], %[^,\n]", eng, kor1);
//        if (readNumber < 2) break; // 데이터가 부족하면 종료
//
//        // 구조체 초기화
//        strcpy(wordList[count].english, eng);
//        strcpy(wordList[count].korean[0], kor1);
//
//        // 두 번째 뜻이 있으면 읽기
//        if (fgetc(dd) == ',') {
//            fscanf(dd, "%[^,\n]", kor2);
//            strcpy(wordList[count].korean[1], kor2);
//        } else {
//            wordList[count].korean[1][0] = '\0'; // 빈 문자열 처리
//        }
//
//        // 세 번째 뜻이 있으면 읽기
//        if (fgetc(dd) == ',') {
//            fscanf(dd, "%[^,\n]", kor3);
//            strcpy(wordList[count].korean[2], kor3);
//        } else {
//            wordList[count].korean[2][0] = '\0'; // 빈 문자열 처리
//        }
//
//        count++;
//    }
//    fclose(dd);
//
//    printf("=== DEBUG: 구조체에 저장된 단어 목록 ===\n");
//    for (int i = 0; i < count; i++) {
//        printf("english = %s, korean[0] = %s, korean[1] = %s, korean[2] = %s\n",
//               wordList[i].english,
//               wordList[i].korean[0],
//               wordList[i].korean[1],
//               wordList[i].korean[2]);
//    }
//    printf("======================================\n");
//}

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
    return count ;
}

// 리눅스 파일 검색
//char whatDictionary[100]; // 파일명 저장용                              FILE *dic = fopen("dic.list", "r");                                     if (!dic) {                                                                 printf("dic.list 파일을 열 수 없습니다.\n");                            return;                                                             }                                                                                                                                               // n번째 파일 이름 가져오기                                             for (int i = 0; i < filenumber; i++) {                                      if (fscanf(dic, "%s", whatDictionary) == EOF) {                             printf("dic.list 파일에서 데이터를 읽는 중 문제가 발생했습니다.\n");
//fclose(dic);
//return;
//}
//}
//fclose(dic);
//
//// 경로 생성
//char add[150] = "2024C_/";
//strcat(add, whatDictionary);
//
//// 단어 수 계산
//*wordCount = countLine(whatDictionary);
//if (*wordCount == 0) {
//printf("파일에 단어가 없습니다.\n");
//return;
//}
//
//FILE *