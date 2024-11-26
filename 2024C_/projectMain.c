#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct {
    char english[15];
    char korean[30]; // ������ �迭, 3�� ��(���ڿ�) ����Ű�� ������
} words;

void input(int, words *wordList);

int randomSelect(FILE *, words *, int *ran);

int main() {
    words word[30];
    int file = 1;
    input(file, word);
    //���� Ȯ���ϴ� ����
    _Bool Finish = 0;

    while (!Finish) {

        printf(">> ���� �ܾ� �ϱ� ���α׷� <<\n");
        printf("1. ���� �ܾ� ���߱�    2. �÷���ī��\n");
        printf("3. ���(hangman)     4. �ܾ��� ����\n");
        printf("5. ���α׷� ����\n");

        int num;
        printf("��ȣ�� �����ϼ���: ");
        scanf("%d", &num);

        //1. ���� �ܾ� ���߱�
        if (num == 1) {
            words words[30];

            int randint = 0;


            int filenumber, outputForm;
            printf("���ϸ�(����) :");
            scanf("%d", &filenumber);

            printf("��� ���(���ĺ� ������� : 1, ������ :2) : ");
            scanf("%d", &outputForm);

            // ���⼭ word�� n.dic�� �ش��ϴ� �ܾ �����
            input(filenumber, words);

            _Bool isFinish = 0;
            do {
                char add[] = "2024C_/";
                char filenum[2];
                itoa(filenumber, filenum, 10); // filenumber ���ڷ� �ٲٱ�

                // ��� ��ġ��
                strcat(add, filenum); //ex . 2024C_/1
                strcat(add, ".dic"); // ex. 2024C_/1.dic

                FILE *dict_Ptr = fopen(add, "r");


                char *answer = malloc(30 * sizeof(char));
                randomSelect(dict_Ptr, words, &randint);
                // �������� ���ܾ� ��� �� �ε��� ��ȯ
                scanf("%s", answer);
                if (strcmp(answer, ".quit") == 0) isFinish = 1;
                else {
                    //����Ȯ��
                    if (strcmp(words[randint].english, answer) == 0) {
                        printf("success\n");
                        //���� ���� ��ġ
                    } else {
                        printf("fail\n");
                    }
                }

                fclose(dict_Ptr);
            } while (!isFinish);


        }

            //2. �÷��� ī��
        else if (num == 2) {

        }

            //3. ���(hangman)
        else if (num == 3) {

        }

            // 4. �ܾ��� ����
        else if (num == 4) {

        }

            //5. ���α׷� ����
        else if (num == 5) {
            Finish = 1;
        }
            // ����ó��
        else {
            printf("��ȿ���� ���� �����Դϴ�. \n");
        }
    }

}

// �������� �����ϱ�

int randomSelect(FILE *fp, words *wordList, int *ran) {
    int random = rand() % 30;
    printf("%s  :", wordList[random].korean);
    *ran = random;
    return *ran;
}


// ���ĺ� ������ �����ϱ�




// dic.list ���� n.dic �����ϱ�
// �׸��� ����ü�� �ش� ��/�� ���� ������ ������ֱ�

void input(int filenumber, words *wordList) {
    char whatDictionary[100]; // dic.list�� ��Ҹ� ����Ű�� ���� ������ ( �� 1.dic, 2.dic ��� )

    FILE *dic; // dic.list�� ���� ���� ���� ������


    // ���� ��� ��� �����ؼ� �־�����ϴ� �� �մϴ�..?�Ф�
    dic = fopen("2024C_/dic.list", "r");
    if (dic == NULL) {
        printf("dic.list �� ����ֽ��ϴ�.");
    }

    for (int i = 0; i < filenumber; i++) {
        fscanf(dic, "%s", whatDictionary);
    }


    printf("%s\n", whatDictionary);
    char add[] = "2024C_/";
    // ��� ��ġ��
    strcat(add, whatDictionary);
    printf("%s\n", add);
    fclose(dic);

    // �Ʊ� ���ĳ��� �ּ��� n.dic�� �����ϱ�
    FILE *dd = fopen(add, "r");


    char eng[15];
    char kor[50];

    for (int i = 0; i < 30; i++) {
        fscanf(dd, "%[^,], %[^\n]\n", eng, kor);
        strcpy(wordList[i].english, eng);
        strcpy(wordList[i].korean, kor);
    }

    //�����: ����� ��µ�
//    for (int i = 0; i < 30; i++) {
//        printf("%s %s\n", wordList[i].english, wordList[i].korean);
//    }
    fclose(dd);

}