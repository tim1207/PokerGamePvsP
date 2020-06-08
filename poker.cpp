#include "header.h"
int main() {
    Card deck[52], temp[13];
    const char* face[] = {  "Deuce","Three", "Four",
                           "Five", "Six", "Seven",
                           "Eight", "Nine", "Ten",
                           "Jack", "Queen",
                           "King", "Ace" };
    const char* suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
    const char* cardType[] = { "���P", "��l", "�G��", "�T��", "���l", "�P��", "��Ī", "�|��", "�P�ᶶ","�@���s" };
    int Control = 1, save = 0, PlayerNum =0, ChangeWithWhom[4], change[4][3], choose[13];
    int score[4] = { 0 };
    int tempscore[4][3] = { 0 };

    srand(time(NULL));


    while (Control != 3) {

        if (Control == 1) {           
            for (int i = 0; i < 4; i++) { // reset
                ChangeWithWhom[i] = 0;
                score[i] = 0;
            }
            printf("�n���w���]�I\n");
            while (PlayerNum != 2 && PlayerNum != 4) {
                printf("�п�J���a�H��(2��4�H)�G");
                cin >> PlayerNum;
            }
            if (PlayerNum == 4) {
                for (int i = 0; i < 2; i++) {
                    printf("�п�J��%d�դ��ۥ洫�P����H(2�ӼƦr)�G", i + 1);
                    cin >> save; 
                    cin >> ChangeWithWhom[save - 1];
                    ChangeWithWhom[save - 1]--;
                }// give  ChangeWithWhom[] value
            }
            else
                ChangeWithWhom[0] = 1;
        }
        else if (Control == 2) {
            fillDeck(deck, face, suit);
            shuffle(deck);
            for (int i = 0; i < 51; i += 13)
                bubble(deck, i, i + 12);
            for (int i = 0; i < PlayerNum * 13; i += 13) {
                cout << endl;
                printf("��%d�쪱�a���P�G\n", i / 13 + 1);
                deal(deck, i, 13);
                printf("��%d�쪱�a�п�J�n�洫��3�i�P�G\n", i / 13 + 1);
                for (int j = 0; j < 3; j++)
                    cin >> change[i / 13][j];
            } //record cards want to change
         
            ChangeCard(deck, ChangeWithWhom, change); //change with order
            for (int i = 0; i < 51; i += 13)
                bubble(deck, i, i + 12);

            for (int i = 0; i < PlayerNum * 13; i += 13) {
                cout << endl;
                printf("��%d�쪱�a���P�G\n", i / 13 + 1);
                deal(deck, i, 13);
                printf("�п�J�n��@�e����3�i�P�G\n");
                for (int j = 0; j < 3; j++)     cin >> choose[j];
                printf("�п�J�n��@������5�i�P�G\n");
                for (int j = 0; j < 5; j++)     cin >> choose[3 + j];
                printf("�п�J�n��@�ᴰ��5�i�P�G\n");
                for (int j = 0; j < 5; j++)     cin >> choose[8 + j];
                for (int j = 0; j < 13; j++)    temp[j] = deck[i + choose[j] - 1];
                FinishSet(deck, temp, i/13);
                //record front middle last pier to choose[],then give it back to deck[]
            }
            for (int i = 0; i < PlayerNum; i++) {
                bubble(deck, i * 13, i * 13 + 2);
                bubble(deck, i * 13 + 3, i * 13 + 7);
                bubble(deck, i * 13 + 8, i * 13 + 12);
                // sorting deck
                if (Straight(deck, i, i + 12) == 9) { //check wheather deck is a dragon
                    tempscore[i][0] = 5000; tempscore[i][1] = 5000; tempscore[i][2] = 5000;
                    printf("%s", cardType[9]); // print �@���s
                    printf("Player%d is winner!", i + 1);
                    score[i] = 3* (PlayerNum-1)*4;//dragon score
                }
            }
            for (int i = 0; i < PlayerNum * 13; i +=13) {
                printf("\n��ƫ�Player%d's cards:\n",i/13+1);
                deal(deck, i, 3);
                tempscore[i/13][0] = givescore(deck, i , i + 2);//��������
                printf("%s\n", cardType[PrintKind(deck, i, i + 2)] );//�C�L�ƫ�
                //printf("%d\n", tempscore[i / 13][0]);
                deal(deck, i + 3, 5);
                tempscore[i/13][1]= givescore(deck, i + 3, i  + 7); // ��������
                printf("%s\n", cardType[PrintKind(deck, i + 3, i + 7)]);//�C�L�ƫ�
                //printf("%d\n", tempscore[i / 13][1]);
                deal(deck, i + 8, 5);                 
                tempscore[i / 13][2]= givescore(deck, i  + 8, i + 12);// ��������
                printf("%s\n", cardType[PrintKind(deck, i + 8, i + 12)]);//�C�L�ƫ�
                //printf("%d\n", tempscore[i / 13][2]);

                if (tempscore[i / 13][0]> tempscore[i / 13][1] || tempscore[i / 13][0] > tempscore[i / 13][2] || tempscore[i / 13][1] > tempscore[i / 13][2]) {
                    printf("(��[�����j�󵥩󤤼[�A���[�����j�󵥩�e�[�A�_�h�����T�[����)!!!\n");
                    tempscore[i / 13][0] = 0;
                    tempscore[i / 13][1] = 0;
                    tempscore[i / 13][2] = 0;
                    // because break the rule so tempscore becomes 0 
                }
            }
            // set score[0-3] compare tempscore[i][0] :front pier
            for (int i = 0; i < PlayerNum;i++) 
                for (int j = 0; j < PlayerNum; j++) {
                    if (tempscore[i][0] > tempscore[j][0])
                        score[i] = score[i] + 1;
                }
            // set score[0-3] compare tempscore[i][1] :middle pier
            for (int i = 0; i < PlayerNum; i++)
                for (int j = 0; j < PlayerNum; j++) {
                    if (tempscore[i][1] > tempscore[j][1])
                        score[i] = score[i] + 1;
                }
            // set score[0-3] compare tempscore[i][2] :last pier
            for (int i = 0; i < PlayerNum; i++)
                for (int j = 0; j < PlayerNum; j++) {
                    if (tempscore[i][2] > tempscore[j][2])
                        score[i] = score[i] + 1;
                }
            for (int i = 0; i < PlayerNum; i++) //print every score
                printf("Player%d score is %d\n", i + 1, score[i]);
            for (int i = 0; i < 4; i++) { // reset tempscore
                for (int j = 0; j < 3; j++)
                    tempscore[i][j] = 0;
            }
            
        }
        printf("�ﶵ\n"
            "   (1)���s�}�l(���]�}�l�n��)\n"
            "   (2)�~��U�@�^ (�U��13�i�P)\n"
            "   (3)�����F\n"
            "�п�J�ﶵ:");
        cin >> Control;
    }																		
    return 0;
}