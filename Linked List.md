# Linked List [연결리스트]
``데이터를 나란히 저장하며, 중복된 데잍의 저장을 막지 않습니다.``
1. 순차 리스트 : 배열을 기반으로 구현된 리스트
2. 연결 리스트 : 메모리의 동적 할당을 기반으로 구현된 리스트

# Abstract Data Type [추상자료형]
- 구체적인 기능의 완성과정을 언급하지 않고, 순수하게 기능이 무엇인지를 나열한 것

# ArrayList.h
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

void ListInit(List* plist);                          //초기화
void LInsert(List* plist, LData data);               //데이터 저장

int LFirst(List* plist, LData* pdata);               //첫 데이터 참조
int LNext(List* plist, LData* pdata);                //두 번째 이후 데이터 참조

LData LRemove(List* plist);                          //참조한 데이터 삭제 
int LCount(List* plist);                             //저장된 데이터의 수 반환

#endif


```

# ListMain.c
```
#include <stdio.h>
#include "ArrayList.h"

void ListInit(List* plist)                           //초기화
{
	(plist->numOfData) = 0;                          //리스트에 저장된 데이터의 수 초기화
	(plist->curPosition) = -1;                       //현재 아무 위치도 가리키지 않음
}

void LInsert(List* plist, LData data)
{
	if (plist->numOfData >= LIST_LEN)
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
	LData rdata = plist->arr[rpos];                  //삭제할 데이터를 임시로 저장

	//삭제를 위한 데이터의 이동을 진행하는 반복문
	for (i = rpos; i < num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];           //한 칸씩 앞(왼쪽)으로 이동 

	(plist->numOfData)--;                            //데이터의 수 감소
	(plist->curPosition)--;                          //참조위치를 하나 앞(왼쪽)으로 이동
	return rdata;                                    //삭제된 데이터의 반환
}
 
int LCount(List* plist)                              //저장된 데이터의 수 반환
{
	return plist->numOfData;
}
```

# Point.h
```
#ifndef __POINT_H__
#define __POINT_H__

typedef struct _point
{
	int xpos;
	int ypos;
} Point;

//Point 변수의 xpos, ypos 값 설정
void SetPointPos(Point* ppos, int xpos, int ypos);

//Point 변수의 xpos, ypos 정보 출력
void ShowPointPos(Point* ppos);

// 두 Point 변수의 비교
int PointComp(Point* pos1, Point* pos2);

#endif
```

# Point.c
```
#include <stdio.h>
#include "Point.h"

//Point 변수의 xpos, ypos 값 설정
void SetPointPos(Point* ppos, int xpos, int ypos)
{
	ppos->xpos = xpos;
	ppos->ypos = ypos;
}

//Point 변수의 xpos, ypos 정보 출력
void ShowPointPos(Point* ppos)
{
	printf("[%d],[%d] \n", ppos->xpos, ppos->ypos);
}

// 두 Point 변수의 비교
int PointComp(Point* pos1, Point* pos2)
{
	if (pos1->xpos == pos2->xpos && pos1->ypos == pos2->ypos)
		return 0;
	else if (pos1->xpos == pos2->xpos)
		return 1;
	else if (pos1->ypos == pos2->ypos)
		return 2;
	else
		return -1;
}
```

# PointListMain.c
```
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"
#include "ArrayList.h"

int main(void)
{
	List list;
	Point compPos;
	Point* ppos;

	ListInit(&list);

	//4개의 데이터 저장
	ppos = (Point*)malloc(sizeof(Point));                          //malloc , free 동적 메모리 할당 및 해제
	SetPointPos(ppos, 2, 1);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));                          
	SetPointPos(ppos, 2, 2);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));                         
	SetPointPos(ppos, 3, 1);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));                          
	SetPointPos(ppos, 3, 2);
	LInsert(&list, ppos);

	//저장된 데이터의 출력

	printf("현재 저장된 데이터의 수 : %d \n", LCount(&list));                //여기까지는 정상적으로 4개 저장된거 확인됨. 이 이후부터 문제가 생긴듯해요.
	
	if (LFirst(&list, &ppos))                                         //책에는 이대로 적혀있는데 똑같이 안나오더라구요. 무엇보다 왜 if문에 조건을 LFirst를 넣는지도 이해가 안가네요 ㅠㅠ..
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}

	printf("\n");


	//xpos가 2인 모든 데이터 삭제

	compPos.xpos = 2;
	compPos.ypos = 0;

	if (LFirst(&list,&ppos))
	{
		if (PointComp(ppos,&compPos)==1)
		{
			ppos = LRemove(&list);
			free(ppos);
		}

		while (LNext(&list,&ppos))
		{
			if (PointComp(ppos,&compPos)==1)
			{
				ppos = LRemove(&list);
				free(ppos);
			}
		}
	}

	//삭제 후 남은 데이터 전체 출력
	printf("현재 데이터의 수 : %d \n", LCount(&list));

	if (LFirst(&list,&ppos))
	{
		ShowPointPos(ppos);

		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}
	printf("\n");

	return 0;

}
```
