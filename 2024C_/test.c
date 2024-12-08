#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
    char english[15];
    char korean[3][30]; // ������ �迭, 3�� ��(���ڿ�) ����Ű�� ������
} words;
void input(int, words *, int *);
int countLine(const char * filename);
void sortStruct(words*, int);
int main() {
    int filenumber =1;
    printf("%d",countLine("2024C_/dic.list"));

}
void sortStruct(words *wordList, int wordCount) {
    words temp; // �ӽ� ����ü ����
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            // �� ������ ����
            if (wordList[i].english[0] == '\0' || wordList[j].english[0] == '\0') continue;

            // ������ ��
            if (strcmp(wordList[i].english, wordList[j].english) > 0) {
                temp = wordList[i];
                wordList[i] = wordList[j];
                wordList[j] = temp;
            }
        }
    }

    // ���� ��� ����� ���
    printf("=== DEBUG: ���ĵ� �ܾ� ��� ===\n");
    for (int i = 0; i < wordCount; i++) {
        if (wordList[i].english[0] != '\0') { // �� ������ ����
            printf("english = %s, korean[0] = %s\n",
                   wordList[i].english, wordList[i].korean[0]);
        }
    }
    printf("================================\n");
}
void input(int filenumber, words *wordList, int *wordCount) {
    char whatDictionary[100]; // ���ϸ� �����
    FILE *dic = fopen("2024C_/dic.list", "r");
    if (!dic) {
        printf("dic.list ������ �� �� �����ϴ�.\n");
        return;
    }

    // n��° ���� �̸� ��������
    for (int i = 0; i < filenumber; i++) {
        if (fscanf(dic, "%s", whatDictionary) == EOF) {
            printf("dic.list ���Ͽ��� �����͸� �д� �� ������ �߻��߽��ϴ�.\n");
            fclose(dic);
            return;
        }
    }
    fclose(dic);

    // ��� ����
    char add[150] = "2024C_/";
    strcat(add, whatDictionary);

    // �ܾ� �� ���
    *wordCount = countLine(add);
    if (*wordCount == 0) {
        printf("���Ͽ� �ܾ �����ϴ�.\n");
        return;
    }

    FILE *dd = fopen(add, "r");
    if (!dd) {
        printf("%s ������ �� �� �����ϴ�.\n", add);
        return;
    }

    char eng[15];
    char kor1[30], kor2[30], kor3[30];
    int count = 0;

    while (count < *wordCount) {
        // �� �ٿ��� �ִ� 3���� ���� ����
        int readNumber = fscanf(dd, "%[^,], %[^,], %[^,], %[^\n]",
                                eng, kor1, kor2, kor3);
        if (readNumber >= 2) { // �ּ� ����� �� 1���� ������ ��
            strcpy(wordList[count].english, eng);
            strcpy(wordList[count].korean[0], kor1);
            if (readNumber >= 3)
                strcpy(wordList[count].korean[1], kor2);
            else
                wordList[count].korean[1][0] = '\0'; // �ʱ�ȭ
            if (readNumber == 4)
                strcpy(wordList[count].korean[2], kor3);
            else
                wordList[count].korean[2][0] = '\0'; // �ʱ�ȭ
        } else {
            // �� ������ ó��
            strcpy(wordList[count].english, "\0");
            strcpy(wordList[count].korean[0], "\0");
            wordList[count].korean[1][0] = '\0';
            wordList[count].korean[2][0] = '\0';
        }
        count++;
    }
    fclose(dd);

    // ����� ���
    printf("=== DEBUG: ����ü�� ����� �ܾ� ��� ===\n");
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
//    char whatDictionary[100]; // ���ϸ� �����
//    FILE *dic = fopen("2024C_/dic.list", "r");
//    if (!dic) {
//        printf("dic.list ������ �� �� �����ϴ�.\n");
//        return;
//    }
//
//    // n��° ���� �̸� ��������
//    for (int i = 0; i < filenumber; i++) {
//        if (fscanf(dic, "%s", whatDictionary) == EOF) {
//            printf("dic.list ���Ͽ��� �����͸� �д� �� ������ �߻��߽��ϴ�.\n");
//            fclose(dic);
//            return;
//        }
//    }
//    fclose(dic);
//
//    // ��� ����
//    char add[150] = "2024C_/";
//    strcat(add, whatDictionary);
//
//    // �ܾ� �� ���
//    *wordCount = countLine(add);
//    if (*wordCount == 0) {
//        printf("���Ͽ� �ܾ �����ϴ�.\n");
//        return;
//    }
//
//    FILE *dd = fopen(add, "r");
//    if (!dd) {
//        printf("%s ������ �� �� �����ϴ�.\n", add);
//        return;
//    }
//
//    char eng[15];
//    char kor1[30], kor2[30], kor3[30];
//    int count = 0;
//
//    while (!feof(dd) && count < *wordCount) {
//        // �� �ٿ��� �ִ� 3���� ���� ����
//        int readNumber = fscanf(dd, "%[^,], %[^,\n]", eng, kor1);
//        if (readNumber < 2) break; // �����Ͱ� �����ϸ� ����
//
//        // ����ü �ʱ�ȭ
//        strcpy(wordList[count].english, eng);
//        strcpy(wordList[count].korean[0], kor1);
//
//        // �� ��° ���� ������ �б�
//        if (fgetc(dd) == ',') {
//            fscanf(dd, "%[^,\n]", kor2);
//            strcpy(wordList[count].korean[1], kor2);
//        } else {
//            wordList[count].korean[1][0] = '\0'; // �� ���ڿ� ó��
//        }
//
//        // �� ��° ���� ������ �б�
//        if (fgetc(dd) == ',') {
//            fscanf(dd, "%[^,\n]", kor3);
//            strcpy(wordList[count].korean[2], kor3);
//        } else {
//            wordList[count].korean[2][0] = '\0'; // �� ���ڿ� ó��
//        }
//
//        count++;
//    }
//    fclose(dd);
//
//    printf("=== DEBUG: ����ü�� ����� �ܾ� ��� ===\n");
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

// ������ ���� �˻�
//char whatDictionary[100]; // ���ϸ� �����                              FILE *dic = fopen("dic.list", "r");                                     if (!dic) {                                                                 printf("dic.list ������ �� �� �����ϴ�.\n");                            return;                                                             }                                                                                                                                               // n��° ���� �̸� ��������                                             for (int i = 0; i < filenumber; i++) {                                      if (fscanf(dic, "%s", whatDictionary) == EOF) {                             printf("dic.list ���Ͽ��� �����͸� �д� �� ������ �߻��߽��ϴ�.\n");
//fclose(dic);
//return;
//}
//}
//fclose(dic);
//
//// ��� ����
//char add[150] = "2024C_/";
//strcat(add, whatDictionary);
//
//// �ܾ� �� ���
//*wordCount = countLine(whatDictionary);
//if (*wordCount == 0) {
//printf("���Ͽ� �ܾ �����ϴ�.\n");
//return;
//}
//
//FILE *