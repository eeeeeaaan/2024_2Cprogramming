#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <synchapi.h>


typedef struct {
    char english[15];
    char korean[30]; // ������ �迭, 3�� ��(���ڿ�) ����Ű�� ������
} words;

void input(int, words *wordList);
void sortStruct(words *wordList);
int randomSelect( words *, int *ran);

//2. flash card
void randomFlash(words *, int *ran, int speed);
int main() {
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




            int filenumber, outputForm;
            printf("���ϸ�(����) :");
            scanf("%d", &filenumber);

            printf("��� ���(���ĺ� ������� : 1, ������ :2) : ");
            scanf("%d", &outputForm);

            // ���⼭ word�� n.dic�� �ش��ϴ� �ܾ �����
            input(filenumber, words);
            _Bool isFinish = 0;

            if(outputForm ==1){ // ���ĺ� ����
                sortStruct(words); // ���� �� �������⸸ �ϸ��.
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
            }else if(outputForm==2){ //������ ����
                int randint = 0;
                do {
                    char *answer = malloc(30 * sizeof(char));
                    randomSelect(words, &randint);
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


                } while (!isFinish);
            }else{
                printf("��ȿ���� ���� ��ȣ�Դϴ�.");
            }




        }

            //2. �÷��� ī��
        else if (num == 2) {
            words word[30];
            int speed, filenumber, outputForm, randint=0;
            printf("�ӵ�(��) :");
            scanf("%d", &speed);
            printf("���ϸ�(����) :");
            scanf("%d", &filenumber);

            printf("��¹��(���ĺ� �������: 1, ������ :2) :");
            scanf("%d", &outputForm);
            // ����ü�� ���
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
                printf("��ȿ���� ���� ��¹�� �Դϴ�. ");
            }

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

// �������� �����ϰ� �ѱ۴ܾ� �������ֱ� (1)
int randomSelect(words *wordList, int *ran) {
    int random = rand() % 30;
    printf("%s  :", wordList[random].korean);
    *ran = random;
    return *ran;
}


// �������� �����ϰ� ����, �ѱ� n�� �������� ������ֱ�
void randomFlash (words *wordList, int *ran, int speed){
    int random = rand() %30 ;
    printf("%s\n", wordList[random].english);
    Sleep(speed *1000);
    printf("%s\n", wordList[random].korean);
}

// ���ĺ� ������ �����ϱ�
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

    char add[] = "2024C_/";
    // ��� ��ġ��
    strcat(add, whatDictionary);

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