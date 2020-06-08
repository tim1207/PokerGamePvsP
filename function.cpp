#include "header.h"

void fillDeck(Card* const wDeck, const char* wFace[], const char* wSuit[]) {
    for (int i = 0; i <= 51; i++) {
        wDeck[i].face = wFace[i / 4];//���Ʀr
        wDeck[i].suit = wSuit[i % 4];//�����
        wDeck[i].ID = i;//���s���A�H��K��j�p
    }
}

void shuffle(Card* const wDeck) {
    int j;
    Card temp;
    for (int i = 0; i <= 51; i++) {//�����üƩ�^wDeck
        j = rand() % 52; //��j�ü� 0-51��
        temp = wDeck[i]; 
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

void deal(const Card* const wDeck, int start, int size) {
    for (int i = start; i < start + size; i++)
        printf("��%d�i \t %5s of %-8s%c", i % 13 + 1, wDeck[i].face, wDeck[i].suit, '\n');
    printf("\n");
}//�L�P�A�Ѽ�:deck:�P,start:�}�l�L���Ĥ@�i end:�L���̫�@�i,size:�L���P�� 




void bubble(Card* const wDeck, int start, int end) {
    for (int i = end; i > start; i--)
        for (int j = start; j < i; j++)
            if (wDeck[j].ID > wDeck[j + 1].ID)//��ID��j�p
                swap(wDeck, j, j + 1);//�洫��i�P
}//�ƦC�P�A�Ѽ�:deck:�P,start:�}�l���Ĥ@�i end:�̫�@�i

void swap(Card* const wDeck, int big, int small) {
    Card temp;
    temp = wDeck[big];
    wDeck[big] = wDeck[small];
    wDeck[small] = temp;
}//�洫��i�P�A�Ѽ�:deck:�P, big:�Ĥ@�i ,small��@�i

void ChangeCard(Card* const wDeck, int ChangeWithWhom[4], int change[4][3]) {
    for (int count = 0; count < 4; count++) {
        if (ChangeWithWhom[count]) {
            for (int i = 0; i < 3; i++)
                swap(wDeck, count * 13 + change[count][i] - 1, ChangeWithWhom[count] * 13 + change[ChangeWithWhom[count]][i] - 1);
        }            //�ھګ��w�����a�諸�P���P
    }
}//�洫4�H���P�A�Ѽ�:deck:�P, ChangeWithWhom:�M�ִ� ,change�n�����P

void FinishSet(Card* const deck, const Card* const temp, int start) {
    for (int i = 0; i < 13; i++)
        deck[start * 13 + i] = temp[i];
}//������X�Ӫ� FRONT MIDDLE LAST PIER �Ǧ^deck�A�Ѽ�:deck:�P,temp :�Ȧs���P,start:�M�w��^deck���_�l��m

int givescore(Card* const wDeck,int start,int end){  
    if (PrintKind(wDeck, start, end) ==8)
        return 1600 + wDeck[end].ID;//"�P�ᶶ������"
    if (PrintKind(wDeck, start, end) == 7)
        return 1400 + wDeck[end - 1].ID % 13;  //"�|��������"
    if (PrintKind(wDeck, start, end) == 6)
        return 1200 + wDeck[end-2].ID % 13; //"��Ī������"
    if (PrintKind(wDeck, start, end) == 5)
        return 1000 + wDeck[end].ID;//"�P�᪺����"
    if (PrintKind(wDeck, start, end) == 4)
        return 800 + wDeck[end].ID;//"���l������"
    if (PrintKind(wDeck, start, end) == 3)
        return 600 + wDeck[end-2].ID %13 ;//"�T��������"
    if (PrintKind(wDeck, start, end) == 2) {
        int i = 0;
        for (i = end; start < i ; i--) {
            if (wDeck[i].ID % 13 == wDeck[i -1].ID % 13)
                break;
        }
        return 400 + wDeck[i].ID;//"�G�諸����"
    }
    if  (PrintKind(wDeck, start, end) == 1) {
        int i = 0;
        for ( i=start; i < end; i++) {
            if (wDeck[i].ID %13 == wDeck[i + 1].ID % 13)
                break;
        }
        return 200 + wDeck[i+1].ID; //"��l������"
    }
     if (PrintKind(wDeck, start, end) == 0)
        return 0 + wDeck[end].ID;//"���P������"
}//�������� �Ѽ�:deck:�P,start:�}�l���Ĥ@�i end:�̫�@�i

int PrintKind(Card* const wDeck, int start, int end)
{
    if (Find_kind(wDeck, start, end) == 0 && Flush(wDeck, start, end) == 5 && Straight(wDeck, start, end) == 4)
        return 8;//"�P�ᶶ"
    if (Find_kind(wDeck, start, end) == 7 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 7;  //"�|��"
    if (Find_kind(wDeck, start, end) == 6 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 6; //"��Ī"
    if (Flush(wDeck, start, end) == 5 && Find_kind(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 5;//"�P��"
    if (Straight(wDeck, start, end) == 4 && Flush(wDeck, start, end) == 0 && Find_kind(wDeck, start, end) == 0)
        return 4;//"���l"
    if (Find_kind(wDeck, start, end) == 3 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 3;//"�T��"
    if (Find_kind(wDeck, start, end) == 2 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 2;//"�G��"
    if (Find_kind(wDeck, start, end) == 1 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0) 
        return 1; //"��l"
    if (Find_kind(wDeck, start, end) == 0 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 0 ;//"���P"
}//�P�_�P�� �Ѽ�:deck:�P,start:�}�l���Ĥ@�i ,end:�̫�@�i 

int Find_kind(Card* const wDeck, int start, int end) {
    int serch[2] = { 0 }, max[2] = { 0 }, now = start, count = 0;
    while (now < end) {
        for (int i = now +1; i <= end; i++) {
            if (wDeck[now].ID / 4 == wDeck[i].ID / 4) {
                now = i;
                serch[count]++;
            }//�䦳�S���P�Ʀr
            else {
                now = i;
                if (serch[count]>0) {
                    if (wDeck[i - 1].ID > max[count])
                        max[count] = wDeck[i - 1].ID;
                    count++;
                }
                break;
            }//�䦳�S���ĤG�զP���
            
        }
    }
    if (serch[0] == 3) //�|���I
        return 7;
    else if (serch[0] + serch[1] == 3) //"��Ī"
        return 6;
    else if (serch[0] == 2)//"�T���I
        return 3;
    else if (serch[0] + serch[1] == 2) //"���I     
        return 2;
    else if (serch[0] == 1) //"���P"
        return 1;
    else 
        return 0;
}// �P�_��l �Ѽ� : deck:�P, start : �}�l���Ĥ@�i, end : �̫�@�i

int Flush(Card* const wDeck, int start, int end) {
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (wDeck[start].suit == wDeck[i].suit)
            count++;
        else
            break;
    }//�䦳�S���P���
    if (count == 4)
        return 5; //flush
    else
        return 0;
}// �P�_�P�� �Ѽ� : deck:�P, start : �}�l���Ĥ@�i, end : �̫�@�i

int Straight(Card* const wDeck, int start, int end) {
    int count = 0;
    for (int i = start; i < end; i++) {
        if (wDeck[i].ID / 4 + 1 == wDeck[i + 1].ID / 4)
            count++;//�O�_�s��
        else if (wDeck[i].ID / 4 + 9 == wDeck[i + 1].ID / 4 && i + 1 == end)
            count++, end--;//�O�_����s��
        else      break;
    }
    if (count == 4)
        return 4;//straight
    else if (count == 12)
        return 9;//dragon
    else
        return 0;
}// �P�_���l �Ѽ� : deck:�P, start : �}�l���Ĥ@�i, end : �̫�@�i