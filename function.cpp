#include "header.h"

void fillDeck(Card* const wDeck, const char* wFace[], const char* wSuit[]) {
    for (int i = 0; i <= 51; i++) {
        wDeck[i].face = wFace[i / 4];//給數字
        wDeck[i].suit = wSuit[i % 4];//給花色
        wDeck[i].ID = i;//給編號，以方便比大小
    }
}

void shuffle(Card* const wDeck) {
    int j;
    Card temp;
    for (int i = 0; i <= 51; i++) {//給予亂數放回wDeck
        j = rand() % 52; //給j亂數 0-51間
        temp = wDeck[i]; 
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

void deal(const Card* const wDeck, int start, int size) {
    for (int i = start; i < start + size; i++)
        printf("第%d張 \t %5s of %-8s%c", i % 13 + 1, wDeck[i].face, wDeck[i].suit, '\n');
    printf("\n");
}//印牌，參數:deck:牌,start:開始印的第一張 end:印的最後一張,size:印的牌數 




void bubble(Card* const wDeck, int start, int end) {
    for (int i = end; i > start; i--)
        for (int j = start; j < i; j++)
            if (wDeck[j].ID > wDeck[j + 1].ID)//用ID比大小
                swap(wDeck, j, j + 1);//交換兩張牌
}//排列牌，參數:deck:牌,start:開始的第一張 end:最後一張

void swap(Card* const wDeck, int big, int small) {
    Card temp;
    temp = wDeck[big];
    wDeck[big] = wDeck[small];
    wDeck[small] = temp;
}//交換兩張牌，參數:deck:牌, big:第一張 ,small後一張

void ChangeCard(Card* const wDeck, int ChangeWithWhom[4], int change[4][3]) {
    for (int count = 0; count < 4; count++) {
        if (ChangeWithWhom[count]) {
            for (int i = 0; i < 3; i++)
                swap(wDeck, count * 13 + change[count][i] - 1, ChangeWithWhom[count] * 13 + change[ChangeWithWhom[count]][i] - 1);
        }            //根據指定的玩家選的牌換牌
    }
}//交換4人的牌，參數:deck:牌, ChangeWithWhom:和誰換 ,change要換的牌

void FinishSet(Card* const deck, const Card* const temp, int start) {
    for (int i = 0; i < 13; i++)
        deck[start * 13 + i] = temp[i];
}//完成選出來的 FRONT MIDDLE LAST PIER 傳回deck，參數:deck:牌,temp :暫存的牌,start:決定放回deck的起始位置

int givescore(Card* const wDeck,int start,int end){  
    if (PrintKind(wDeck, start, end) ==8)
        return 1600 + wDeck[end].ID;//"同花順的分數"
    if (PrintKind(wDeck, start, end) == 7)
        return 1400 + wDeck[end - 1].ID % 13;  //"四條的分數"
    if (PrintKind(wDeck, start, end) == 6)
        return 1200 + wDeck[end-2].ID % 13; //"葫蘆的分數"
    if (PrintKind(wDeck, start, end) == 5)
        return 1000 + wDeck[end].ID;//"同花的分數"
    if (PrintKind(wDeck, start, end) == 4)
        return 800 + wDeck[end].ID;//"順子的分數"
    if (PrintKind(wDeck, start, end) == 3)
        return 600 + wDeck[end-2].ID %13 ;//"三條的分數"
    if (PrintKind(wDeck, start, end) == 2) {
        int i = 0;
        for (i = end; start < i ; i--) {
            if (wDeck[i].ID % 13 == wDeck[i -1].ID % 13)
                break;
        }
        return 400 + wDeck[i].ID;//"二對的分數"
    }
    if  (PrintKind(wDeck, start, end) == 1) {
        int i = 0;
        for ( i=start; i < end; i++) {
            if (wDeck[i].ID %13 == wDeck[i + 1].ID % 13)
                break;
        }
        return 200 + wDeck[i+1].ID; //"對子的分數"
    }
     if (PrintKind(wDeck, start, end) == 0)
        return 0 + wDeck[end].ID;//"散牌的分數"
}//給予分數 參數:deck:牌,start:開始的第一張 end:最後一張

int PrintKind(Card* const wDeck, int start, int end)
{
    if (Find_kind(wDeck, start, end) == 0 && Flush(wDeck, start, end) == 5 && Straight(wDeck, start, end) == 4)
        return 8;//"同花順"
    if (Find_kind(wDeck, start, end) == 7 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 7;  //"四條"
    if (Find_kind(wDeck, start, end) == 6 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 6; //"葫蘆"
    if (Flush(wDeck, start, end) == 5 && Find_kind(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 5;//"同花"
    if (Straight(wDeck, start, end) == 4 && Flush(wDeck, start, end) == 0 && Find_kind(wDeck, start, end) == 0)
        return 4;//"順子"
    if (Find_kind(wDeck, start, end) == 3 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 3;//"三條"
    if (Find_kind(wDeck, start, end) == 2 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 2;//"二對"
    if (Find_kind(wDeck, start, end) == 1 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0) 
        return 1; //"對子"
    if (Find_kind(wDeck, start, end) == 0 && Flush(wDeck, start, end) == 0 && Straight(wDeck, start, end) == 0)
        return 0 ;//"散牌"
}//判斷牌型 參數:deck:牌,start:開始的第一張 ,end:最後一張 

int Find_kind(Card* const wDeck, int start, int end) {
    int serch[2] = { 0 }, max[2] = { 0 }, now = start, count = 0;
    while (now < end) {
        for (int i = now +1; i <= end; i++) {
            if (wDeck[now].ID / 4 == wDeck[i].ID / 4) {
                now = i;
                serch[count]++;
            }//找有沒有同數字
            else {
                now = i;
                if (serch[count]>0) {
                    if (wDeck[i - 1].ID > max[count])
                        max[count] = wDeck[i - 1].ID;
                    count++;
                }
                break;
            }//找有沒有第二組同花色
            
        }
    }
    if (serch[0] == 3) //四條！
        return 7;
    else if (serch[0] + serch[1] == 3) //"葫蘆"
        return 6;
    else if (serch[0] == 2)//"三條！
        return 3;
    else if (serch[0] + serch[1] == 2) //"兩對！     
        return 2;
    else if (serch[0] == 1) //"散牌"
        return 1;
    else 
        return 0;
}// 判斷對子 參數 : deck:牌, start : 開始的第一張, end : 最後一張

int Flush(Card* const wDeck, int start, int end) {
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (wDeck[start].suit == wDeck[i].suit)
            count++;
        else
            break;
    }//找有沒有同花色
    if (count == 4)
        return 5; //flush
    else
        return 0;
}// 判斷同花 參數 : deck:牌, start : 開始的第一張, end : 最後一張

int Straight(Card* const wDeck, int start, int end) {
    int count = 0;
    for (int i = start; i < end; i++) {
        if (wDeck[i].ID / 4 + 1 == wDeck[i + 1].ID / 4)
            count++;//是否連號
        else if (wDeck[i].ID / 4 + 9 == wDeck[i + 1].ID / 4 && i + 1 == end)
            count++, end--;//是否有跨連號
        else      break;
    }
    if (count == 4)
        return 4;//straight
    else if (count == 12)
        return 9;//dragon
    else
        return 0;
}// 判斷順子 參數 : deck:牌, start : 開始的第一張, end : 最後一張