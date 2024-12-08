#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <synchapi.h>


typedef struct {
    char english[15];
    char korean[3][30]; // ������ �迭, 3�� ��(���ڿ�) ����Ű�� ������
} words;

void input(int, words *wordList, int *);
void sortStruct(words *wordList, int*);
int randomSelect( words *, int *ran);
int countLine(const char*);
//2. flash card
void randomFlash(words *, int *ran, int speed);

// 4. �ܾ��� ����
void addWord(int);
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

            int filenumber, outputForm, countLine=0;
            printf("���ϸ�(����) :");
            scanf("%d", &filenumber);

            printf("��� ���(���ĺ� ������� : 1, ������ :2) : ");
            scanf("%d", &outputForm);

            // ���⼭ word�� n.dic�� �ش��ϴ� �ܾ �����
            input(filenumber, words, &countLine);
            _Bool isFinish = 0;
            int rightProblem  =0 , allProblem=0 ;

            if(outputForm ==1){ // ���ĺ� ����
                double score ;

                sortStruct(words, &countLine); // ���� �� �������⸸ �ϸ��.
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
            }else if(outputForm==2){ //������ ����
                double score;
                int randint = 0;
                do {
                    char *answer = malloc(30 * sizeof(char));
                    randomSelect(words, &randint);
                    // �������� ���ܾ� ��� �� �ε��� ��ȯ
                    scanf("%s", answer);
                    if (strcmp(answer, ".quit") == 0) {
                        score = (double)rightProblem/ allProblem;
                        printf("%.2lf\n", 100*score);
                        isFinish = 1;
                    }
                    else {
                        //����Ȯ��
                        if (strcmp(words[randint].english, answer) == 0) {
                            printf("success\n");
                            rightProblem ++;
                            allProblem++;
                            //���� ���� ��ġ
                        } else {
                            printf("fail\n");
                            allProblem++;
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
            int speed, filenumber, outputForm, randint=0, countLine=0;
            printf("�ӵ�(��) :");
            scanf("%d", &speed);
            printf("���ϸ�(����) :");
            scanf("%d", &filenumber);

            printf("��¹��(���ĺ� �������: 1, ������ :2) :");
            scanf("%d", &outputForm);
            // ����ü�� ���
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
                printf("��ȿ���� ���� ��¹�� �Դϴ�. ");
            }

        }

            //3. ���(hangman)
        else if (num == 3) {

        }

            // 4. �ܾ��� ����
        else if (num == 4) {
            // �ܾ��� ���� �޴���.. ��°� ���� �Ҹ��ΰ�?
            _Bool toMainWordList =0;
            while(!toMainWordList){
                system("cls"); // linux ������ ���Ӱ� �ٲ������
                Sleep(300);
                printf("1. �� ���� �߰��ϱ�     2. �� �ܾ� �߰��ϱ�\n");
                printf("3. �ܾ��� ����         4. �ܾ� ���� ��� ����\n");
                printf("5. �ܾ��� ���� ����\n");


                int num, countLine=0 ;
                printf("��ȣ�� �Է��ϼ��� :");
                scanf("%d", &num);



                //�Է� ���� ����...
                int c ;
                while((c= getchar())!='\n' && c != EOF);

                if(num==1){

                    char n ;
                    int count=0;

                    // ���� dic �� ���� ( ���� \n ����ؼ� ) ���� ������ ��Ʈ ���������
                    FILE *fileList = fopen("2024C_/dic.list", "r");
                    while(fscanf(fileList, "%c",&n) != EOF){
                        if(n == '\n'){
                            count++;
                        }
                    }
                    fclose(fileList);


                    // dic.list�� �߰��ϱ�
                    FILE *writeList = fopen("2024C_/dic.list", "a");

                    fprintf(writeList, "\n%d.dic",count+2);
                    fclose(writeList);

                    // �ܾ� �߰��ϱ�
                    addWord(count+2);


                }
                else if (num==2){
                    printf("���ϸ�(����) :");
                    int day ;
                    scanf("%d", &day);
                    addWord(day);

                }
                else if(num==3){
                    printf("���ϸ�(����) :");
                    int days;
                    words word[30] ;
                    scanf("%d", &days);
                    input(days, word,&countLine );
                    printf("-----�ܾ���---------\n");
                    for(int i =0 ;i<countLine; i++){
                        printf("%s ", word[i].english);
                        printf("%s\n", word[i].korean[0]);

                    }
                    printf("\n");

                }
                else if(num==4){
                    printf("-------�ܾ� ���� ���-----------");
                    FILE *fp = fopen("2024C_/dic.list", "r");

                }
                else{
                    toMainWordList=1;
                }
            }

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
    *ran = random;
    printf("%s  ->", wordList[random].korean[0]);
    return *ran;
}


// �������� �����ϰ� ����, �ѱ� n�� �������� ������ֱ�
void randomFlash (words *wordList, int *ran, int speed){
    int random = rand() %30 ;
    printf("%s\n", wordList[random].english);
    Sleep(speed*1000);

    printf("%s\n", wordList[random].korean[0]);

}

// ���ĺ� ������ �����ϱ�
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
//    printf("=== DEBUG: ���ĵ� �ܾ� ��� ===\n");
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


// dic.list ���� n.dic �����ϱ�
// �׸��� ����ü�� �ش� ��/�� ���� ������ ������ֱ�
void input(int filenumber, words *wordList, int *wordCount) {
    char whatDictionary[100]; // ���ϸ� �����
    FILE *dic = fopen("2024C_/dic.list", "r");

    // ������������ �̷���
    // FILE *dic = fopen("dic.list", "r");
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


    // clion ����
    // ��� ����
    char add[150] = "2024C_/";
    strcat(add, whatDictionary);
    // ������������ �� ���� ���ְ� �׳� �Ʒ� countLine �ȿ� add ���� whatDictionary ������ ��
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
    //


    char eng[15];
    char kor1[30], kor2[30], kor3[30];
    int count = 0;

    while (count < *wordCount) {
        // �� �ٿ��� �ִ� 3���� ���� ����
        int readNumber = fscanf(dd, " %[^,\n], %[^,\n]", eng, kor1);
        if (readNumber < 2) break; // �����Ͱ� �����ϸ� ����

        // ����ü �ʱ�ȭ
        strcpy(wordList[count].english, eng);
        strcpy(wordList[count].korean[0], kor1);

        // �� ��° ���� ������ �б�
        if (fgetc(dd) == ',') {
            fscanf(dd, "%[^,\n]", kor2);
            strcpy(wordList[count].korean[1], kor2);
        } else {
            wordList[count].korean[1][0] = '\0'; // �� ���ڿ� ó��
        }

        // �� ��° ���� ������ �б�
        if (fgetc(dd) == ',') {
            fscanf(dd, "%[^,\n]", kor3);
            strcpy(wordList[count].korean[2], kor3);
        } else {
            wordList[count].korean[2][0] = '\0'; // �� ���ڿ� ó��
        }

        count++;
    }
    fclose(dd);

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


void addWord(int day){
    // ������������ ndic�� address ��� file add �� �����Ѵܴ�.
    char address[50]="2024C_/";
    char fileadd[20] ;


    sprintf(fileadd, "%d.dic", day);
    strcat(address, fileadd);


    FILE *ndic = fopen(address, "a");

    _Bool isFinish =0 ;
    int word_count =0 ;
    char word_mean[50], english[50], korean[50];

    while(!isFinish){
        //�Է¹ޱ�...
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