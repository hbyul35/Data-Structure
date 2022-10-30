# Linked List [연결리스트]
``데이터를 나란히 저장하며, 중복된 데이터의 저장을 막지 않습니다.``
1. 순차 리스트 : 배열을 기반으로 구현된 리스트
2. 연결 리스트 : 메모리의 동적 할당을 기반으로 구현된 리스트

# Abstract Data Type [추상자료형]
- 구체적인 기능의 완성과정을 언급하지 않고, 순수하게 기능이 무엇인지를 나열한 것


## ArrayList.h
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

## ListMain.c
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

## Point.h
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

## Point.c
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

## PointListMain.c
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
# 연결리스트의 활용

## LinkedRead.c
```
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;                                             // 데이터를 담을 공간
	struct _node* next;                                   // 연결의 도구
} Node;

int main(void)
{
	Node* head = NULL;                                    // 리스트의 머리를 가리키는 포인터 변수
	Node* tail = NULL;                                    // 리스트의 꼬리를 가리키는 포인터 변수
	Node* cur = NULL;                                     // 저장된 데이터의 조회에 사용되는 포인터 변수

	Node* newNode = NULL;
	int readData;

	//데이터 입력받는 과정
	while (1)
	{
		printf("자연수 입력 : ");
		scanf_s("%d", &readData);
		if (readData < 1)
			break;

		//노드의 추가 과정
		newNode = (Node*)malloc(sizeof(Node));            // 노드(바구니)의 생성
		newNode->data = readData;                         // 노드에 데이터 저장
		newNode->next = NULL;                             // 노드의 next를 NULL로 초기화

		if (head == NULL)                                 // 첫 번째 노드라면
			head = newNode;                               // 첫 번째 노드를 head가 가리키게 함
		else tail->next = newNode;                        // 두 번째 이후 노드라면 tail 뒤 노드에 연결

		tail = newNode;                                   // 노드의 끝을 tail이 가리키게 함
	}
	printf("\n");

	//입력받은 데이터의 출력과정
	printf("전체 출력 \n");

	if (head == NULL)
		printf("자연수가 존재하지 않습니다.");
	else
	{
		cur = head;                                      // cur이 리스트의 첫 번째 노드를 가리킨다.
		printf("%d ", cur->data);                        //첫 번째 데이터 출력

		while (cur->next != NULL)                       // 연결된 노드가 존재할 경우
		{
			cur = cur->next;                            // cur이 다음 노드를 가리키게 한다.
			printf("%d ", cur->data);                   // cur이 가리키는 노드를 출력한다.
		}
	}
	printf("\n\n");
	
	//메모리의 해제과정
	if (head == NULL)                                  //해제 할 노드가 존재하지 않음
		return 0;
	else
	{
		Node* delNode = head;
		Node* delNextNode = head->next;

		printf("%d을(를) 삭제합니다. \n", head->data);
		free(delNode);                                   //첫 번째 노드 삭제

		while (delNextNode != NULL)                      //두 번째 이후 노드 삭제
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d을(를) 삭제합니다. \n", delNode->data);
			free(delNode);                                   
		}
	}
	return 0;
}
```

<hr/>

# 더미 노드 기반 단순 연결 리스트

## DLinkedList.h
```
#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

#define TRUE 1
#define FALSE 0

typedef int LData;

typedef struct _node
{
	LData data;
	struct _node* next;
} Node;

typedef struct _linkedList
{
	Node* head;                                                      // 더미 노드를 가리키는 멤버
	Node* cur;                                                       // 참조 및 삭제를 돕는 멤버(더미 다음 첫 번째 노드)
	Node* before;                                                    // 삭제를 돕는 멤버(더미노드 가리킴)
	int numOfData;                                                   // 저장된 데잍의 수를 기록하기 위한 멤버
	int (*comp)(LData d1, LData d2);                                 // 정렬의 기준을 등록하기 위한 멤버
} LinkedList;

typedef LinkedList List;

void ListInit(List* plist);
void LInsert(List* plist, LData data);

int LFirst(List* plist, LData* pdata);
int LNext(List* plist, LData* pdata);

LData LRemove(List* plist);
LData LCount(List* plist);

void SetSortRule(List* plist, int (*comp)(LData d1, LData d2));

#endif

```
## DLinkedList.c
```
#include "DLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void ListInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));                        // 더미노드 생성
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = NULL;
}

void FInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));                      // 새 노드 생성
	newNode->data = data;                                             // 새 노드에 데이터 저장

	newNode->next = plist->head->next;                                // 새 노드가 더미 노드(head) 다음을 가리키게 함
	plist->head->next = newNode;                                      // 더미 노드가 새 노드를 가리키게 함

	(plist->numOfData)++;
}

void SInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));                      // 새 노드 생성
	Node* pred = plist->head;                                         // pred는 더미 노드를 가리킴
	newNode->data = data;                                             // 새 노드에 데이터 저장

	// 새 노드가 들어갈 위치를 찾기 위한 반복문
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)        //pred가 마지막 노드도 아니고, 새 데이터가 들어갈 자리를 찾지 못했다면
	{
		pred = pred->next;                                            // 다음 노드로 이동
	}

	newNode->next = pred->next;                                       // 새 노드의 오른쪽을 연결
	pred->next = newNode;                                             // 새 노드의 왼쪽을 연결

	(plist->numOfData)++;                                             // 저장된 데이터의 수 하나 증가
}

void LInsert(List* plist, LData data)
{
	if (plist->comp == NULL)                                          // 정렬 기준이 마련되지 않았다면
		FInsert(plist, data);                                         // 머리에 노드 추가
	else                                                              // 정렬 기준이 마련되었다면
		SInsert(plist, data);                                         // 정렬 기준에 근거하여 노드 추가
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->head->next == NULL)                                    // 더미 노드가 NULL을 가리킨다면
		return FALSE;                                                 // 반환할 데이터가 없다
	
	plist->before = plist->head;                                      // before는 더미 노드를 가리킨다
	plist->cur = plist->head->next;                                   // cur은 첫 번째 노드(더미 다음)를 가리킨다

	*pdata = plist->cur->data;                                        // 첫 번째 노드에 데이터 전달
	return TRUE;                                                      // 데이터 반환 성공
}

int LNext(List* plist, LData* pdata)
{
	if (plist->cur->next == NULL)                                     // cur이 NULL을 가리킨다면
		return FALSE;                                                 // 반환할 데이터가 없다

	plist->before = plist->cur;                                       // cur이 가리키던걸 before가 가리킨다
	plist->cur = plist->cur->next;                                    // cur은 그 다음 노드를 가리킨다

	*pdata = plist->cur->data;                                        // cur이 가리키는 노드에 데이터를 전달
	return TRUE;                                                      // 데이터 반환 성공
}

LData LRemove(List* plist)
{
	Node* rpos = plist->cur;                                          // 소멸 대상의 주소 값을 rpos에 저장
	LData rdata = rpos->data;                                         // 소멸 대상의 데이터를 rdata에 저장

	plist->before->next = plist->cur->next;                           // 소멸 대상을 리스트에서 제거
	plist->cur = plist->before;                                       // cur이 가리키는 위치를 before(이전 노드)로 재조정

	free(rpos);                                                       // 리스트에서 제거된 노드 소멸
	(plist->numOfData)--;                                             // 저장된 데이터의 수 하나 감소
	return rdata;                                                     // 제거된 노드의 데이터 반환
}

LCount(List* plist)
{
	return plist->numOfData;
}

void SetSortRule(List* plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp;
}
```
## DLinkdeListSortMain.c
```
#include <stdio.h>
#include "DLinkedList.h"

int WhoIsPrecede(int d1, int d2)
{
	if (d1 < d2)
		return 0;                                             // d1이 정렬 순서상 앞선다.
	else
		return 1;                                             // d2가 정렬 순서상 앞서거나 같다.
}

int main(void)
{
	//리스트의 생성 및 초기화
	List list;
	int data;
	ListInit(&list);

	SetSortRule(&list, WhoIsPrecede);                         // 정렬 기준 등록
	
	//5개 데이터 저장
	LInsert(&list, 33); LInsert(&list, 11);
	LInsert(&list, 22); LInsert(&list, 22);
	LInsert(&list, 11);

	//저장된 데이터의 전체 출력
	printf("현재 데이터의 수 : %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		while(LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");

	//숫자 22 검색해 모두 삭제
	if (LFirst(&list, &data))
	{
		if (data == 22)
			LRemove(&list);

		while (LNext(&list, &data))
		{
			if (data == 22)
				LRemove(&list);
		}
	}

	// 삭제 후 남아있는 데이터 전체 출력
	printf("현재 데이터의 수 : %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");
	return 0;
}
```

# Circular Linked List

## CLinkedList_h
```
#include <stdio.h>
#include "CLinkedList.h"

int main()
{
	//원형 연결 리스트의 생성 및 초기화
	List list;
	int data, i, nodeNum;
	ListInit(&list);

	//리스트에 5개의 데이터 저장
	LInsert(&list, 3);
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsertFront(&list, 2);
	LInsertFront(&list, 1);

	//리스트에 저장된 데이터를 연속 3회 출력
	if (LFirst(&list, &data))                                        // 첫 번째 데이터 조회했을 때
	{
		printf("%d ", data);

		for ( i = 0; i < LCount(&list)*3-1; i++)
		{
			if (LNext(&list, &data))
				printf("%d ", data);
		}
	}
	printf("\n");

	// 2의 배수를 찾아서 모두 삭제
	nodeNum = LCount(&list);

	if (nodeNum != 0)
	{
		LFirst(&list, &data);
		if (data % 2 == 0)
			LRemove(&list);

		for (i = 0; i < nodeNum - 1; i++)
		{
			LNext(&list, &data);
			if (data % 2 == 0)
				LRemove(&list);
		}
	}

	// 전체 데이터 1회 출력
	if (LFirst(&list,&data))
	{
		printf("%d ", data);

		for (i = 0; i < LCount(&list)-1; i++)
		{
			if (LNext(&list, &data))
				printf("%d ", data);
		}
	}
	return 0;
}
```

## CLinkdelist.c
```
#include <stdio.h>
#include <stdlib.h>
#include "CLinkedList.h"

void ListInit(List* plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

void LInsertFront(List* plist, Data data)                                  // 머리에 노드 추가
{
	Node* newNode = (Node*)malloc(sizeof(Node));                           // 새 노드 생성
	newNode->data = data;                                                  // 새 노드에 데이터 저장

	if (plist->tail == NULL)                                               // 첫 번째 노드라면
	{
		plist->tail = newNode;                                             // tail이 새 노드를 가리키게 한다.
		newNode->next = newNode;                                           // 새 노드 자신을 가리키게 한다.
	}
	else
	{
		newNode->next = plist->tail->next;                                 
		plist->tail->next = newNode;                                       
	}

	(plist->numOfData)++;
}

void LInsert(List* plist, Data data)                                       // 꼬리에 노드 추가
{
	Node* newNode = (Node*)malloc(sizeof(Node));                           // 새 노드 생성
	newNode->data = data;                                                  // 새 노드에 데이터 저장

	if (plist->tail == NULL)                                               // 첫 번째 노드라면
	{
		plist->tail = newNode;                                             // tail이 새 노드를 가리키게 한다.
		newNode->next = newNode;                                           // 새 노드 자신을 가리키게 한다.
	}
	else
	{
		newNode->next = plist->tail->next;                                 // newNode를 tail 다음 노드 뒤로 연결
		plist->tail->next = newNode;                                       // tail 다음을 newNode 뒤에 연결 
		plist->tail = newNode;                                             // tail을 newNode와 연결
	}

	(plist->numOfData)++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->tail == NULL)                                                 // 저장된 노드가 없다면
		return FALSE;
	
	// cur과 before의 초기화
	plist->before = plist->tail;                                             // before는 tail 가리키게 한다.
	plist->cur = plist->tail->next;                                          // cur은 tail의 다음(머리)을 가리키게 한다.

	*pdata = plist->cur->data;                                               // cur이 가리키는 노드의 데이터 반환
	return TRUE;

}

int LNext(List* plist, Data* pdata)
{
	if (plist->tail == NULL)                                                 // 저장된 노드가 없다면
		return FALSE;

	plist->before = plist->cur;                                              // before가 다음 노드 가리킴
	plist->cur = plist->cur->next;                                           // cur이 다음 노드 가리킴

	*pdata = plist->cur->data;                                               // cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

Data LRemove(List* plist)
{
	Node* rpos = plist->cur;
	Data rdata = rpos->data;

	if (rpos == plist->tail )                                               // 삭제 대상이 tail을 가리키는 경우
	{
		if (plist->tail == plist->tail->next)                                // and 마지막 남은 노드라면
			plist->tail = NULL;
		else
			plist->tail = plist->before;                                     // tail을 한 칸 뒤로 이동
	}

	plist->before->next = plist->cur->next;                                  // before을 cur 다음 노드와 연결
	plist->cur = plist->before;                                              // cur을 한 칸 앞 before로 이동

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List* plist)
{
	return plist->numOfData;
}
```

## CLinkdeListMain.c
```
#include <stdio.h>
#include <stdlib.h>
#include "CLinkedList.h"

void ListInit(List* plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

void LInsertFront(List* plist, Data data)                                  // 머리에 노드 추가
{
	Node* newNode = (Node*)malloc(sizeof(Node));                           // 새 노드 생성
	newNode->data = data;                                                  // 새 노드에 데이터 저장

	if (plist->tail == NULL)                                               // 첫 번째 노드라면
	{
		plist->tail = newNode;                                             // tail이 새 노드를 가리키게 한다.
		newNode->next = newNode;                                           // 새 노드 자신을 가리키게 한다.
	}
	else
	{
		newNode->next = plist->tail->next;                                 
		plist->tail->next = newNode;                                       
	}

	(plist->numOfData)++;
}

void LInsert(List* plist, Data data)                                       // 꼬리에 노드 추가
{
	Node* newNode = (Node*)malloc(sizeof(Node));                           // 새 노드 생성
	newNode->data = data;                                                  // 새 노드에 데이터 저장

	if (plist->tail == NULL)                                               // 첫 번째 노드라면
	{
		plist->tail = newNode;                                             // tail이 새 노드를 가리키게 한다.
		newNode->next = newNode;                                           // 새 노드 자신을 가리키게 한다.
	}
	else
	{
		newNode->next = plist->tail->next;                                 // newNode를 tail 다음 노드 뒤로 연결
		plist->tail->next = newNode;                                       // tail 다음을 newNode 뒤에 연결 
		plist->tail = newNode;                                             // tail을 newNode와 연결
	}

	(plist->numOfData)++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->tail == NULL)                                                 // 저장된 노드가 없다면
		return FALSE;
	
	// cur과 before의 초기화
	plist->before = plist->tail;                                             // before는 tail 가리키게 한다.
	plist->cur = plist->tail->next;                                          // cur은 tail의 다음(머리)을 가리키게 한다.

	*pdata = plist->cur->data;                                               // cur이 가리키는 노드의 데이터 반환
	return TRUE;

}

int LNext(List* plist, Data* pdata)
{
	if (plist->tail == NULL)                                                 // 저장된 노드가 없다면
		return FALSE;

	plist->before = plist->cur;                                              // before가 다음 노드 가리킴
	plist->cur = plist->cur->next;                                           // cur이 다음 노드 가리킴

	*pdata = plist->cur->data;                                               // cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

Data LRemove(List* plist)
{
	Node* rpos = plist->cur;
	Data rdata = rpos->data;

	if (rpos == plist->tail )                                               // 삭제 대상이 tail을 가리키는 경우
	{
		if (plist->tail == plist->tail->next)                                // and 마지막 남은 노드라면
			plist->tail = NULL;
		else
			plist->tail = plist->before;                                     // tail을 한 칸 뒤로 이동
	}

	plist->before->next = plist->cur->next;                                  // before을 cur 다음 노드와 연결
	plist->cur = plist->before;                                              // cur을 한 칸 앞 before로 이동

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List* plist)
{
	return plist->numOfData;
}
```
