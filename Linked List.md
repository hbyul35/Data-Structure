# Linked List [연결리스트]
``데이터를 나란히 저장하며, 중복된 데잍의 저장을 막지 않습니다.``
1. 순차 리스트 : 배열을 기반으로 구현된 리스트
2. 연결 리스트 : 메모리의 동적 할당을 기반으로 구현된 리스트

# Abstract Data Type [추상자료형]
- 구체적인 기능의 완성과정을 언급하지 않고, 순수하게 기능이 무엇인지를 나열한 것

```
#include <stdio.h>
#ifndef __ARRAY_LIST_H__                           //ifndef : 변수가 정의되어있지않으면 발생
#define __ARRAY_LIST_H__

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100
typedef int LData;                                  //list에 int형 데이터 저장을 위한 선언

typedef struct __ArrayList                          //배열기반 리스트를 정의한 구조체
{
	LData arr[LIST_LEN];                            //리스트의 저장소인 배열
	int numOfData;                                  //저장된 데이터의 수
	int curPosition;                                //데이터 참조위치를 기억
} ArrayList;

typedef ArrayList List;                              //배열기반 리스트 

void ListInit(List* plist)                           //초기화
{
	(plist->numOfData) = 0;                          //리스트에 저장된 데이터의 수 초기화
	(plist->curPosition) = -1;                       //현재 아무 위치도 가리키지 않음
}
void LInsert(List* plist, LData data)                
{
	if (plist->numOfData >=LIST_LEN)
	{
		puts("저장공간이 부족합니다.");
		return;
	}

	plist->arr[plist->numOfData] = data;              //데이터 저장
	(plist->numOfData)++;                             //저장된 데이터의 수 증가
}

int LFirst(List* plist, LData* pdata)                //첫 번째 조회
{
	if (plist->numOfData = 0)                        //저장된 데이터가 없을 경우
		return FALSE;

	(plist->curPosition) = 0;                         //참조 위치 초기화
	*pdata = plist->arr[0];                           //pdata 가리키는 위치에 데이터 저장
	return TRUE;

}
int LNext(List* plist, LData* pdata)                 //두 번째 이후 데이터 참조
{
	if (plist->numOfData = 0)                        //저장된 데이터가 없을 경우
		return FALSE;

	(plist->numOfData)++;                            
	*pdata = plist->arr[plist->curPosition];
	return TRUE;
}

LData LRemove(List* plist)                           //참조한 데이터 삭제
{
	int rpos = plist->curPosition;                   //삭제할 데이터의 인덱스 값 참조
	int num = plist->numOfData;
	int i;
	LData rdata = plist->arr[rpos];                  //
}
int LCount(List* plist);                             //저장된 데이터의 수 반환

#endif

```
