#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <time.h>
using namespace std;
struct card {
    const char* face;
    const char* suit;
    int ID;
};
typedef struct card Card;
void fillDeck(Card* const, const char* [], const char* []);	// �]�P��l��
void shuffle(Card* const);	// �~�P
void deal(const Card* const, int, int);//�L�P
void bubble(Card* const, int, int);//�ƦC
void swap(Card* const, int, int);//�洫��i��
void ChangeCard(Card* const, int[4], int[4][3]);//�洫���a��
void FinishSet(Card* const, const Card* const, int);//�]�mfront middle last pier
int givescore(Card* const wDeck, int start, int end);//����
int PrintKind(Card* const wDeck, int start, int end);//�����ȡA�M�P�_�ƫ�
int Find_kind(Card* const, int, int);//���l
int Flush(Card* const, int, int);//��P��
int Straight(Card* const, int, int);//�䶶�l