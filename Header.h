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
void fillDeck(Card* const, const char* [], const char* []);	// 設牌初始值
void shuffle(Card* const);	// 洗牌
void deal(const Card* const, int, int);//印牌
void bubble(Card* const, int, int);//排列
void swap(Card* const, int, int);//交換兩張排
void ChangeCard(Card* const, int[4], int[4][3]);//交換玩家排
void FinishSet(Card* const, const Card* const, int);//設置front middle last pier
int givescore(Card* const wDeck, int start, int end);//給分
int PrintKind(Card* const wDeck, int start, int end);//給予值，和判斷排型
int Find_kind(Card* const, int, int);//找對子
int Flush(Card* const, int, int);//找同花
int Straight(Card* const, int, int);//找順子