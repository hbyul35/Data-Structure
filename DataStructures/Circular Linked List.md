

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

# DoublyLinkedList (양방향 연결 리스트)

## DBLinkedList.h
```
#ifndef __DBLINKED_LISH_H__
#define __DBLINKED_LISH_H__

#define TRUE          1
#define FALSE         0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
	struct _node* prev;
}Node;

typedef struct _DLinkedList
{
	Node* head;
	Node* cur;
	int numOfData;
}DBLinkedList;

typedef DBLinkedList List;

void ListInit(List* plist);
void LInsert(List* plist, Data data);

int LFirst(List* plist, Data* pdata);
int LNext(List* plist, Data* pdata);
int LPrevious(List* plist, Data* pdata);
int LCount(List* plist);

#endif
```

## DBLinkedList.cpp
```
#include <stdio.h>
#include <stdlib.h>
#include "DBLinkedList.h"

void ListInit(List* plist)
{
	plist->head = NULL;
	plist->numOfData = 0;
}

void LInsert(List* plist, Data data)
{
	Node* newNode = new Node;                                    // 새 노드 생성
	newNode->data = data;

	// 여기서 초기 plist->head는 NULL
	newNode->next = plist->head;                                 // 새 노드가 기존 노드를 가리키게 한다
	if (plist->head != NULL)                                     // 두 번째 이후 노드를 추가할 때만 실행
		plist->head->prev = newNode;                             // 기존 노드가 새 노드를 가리키게 한다

	newNode->prev = NULL;                                        // 새 노드의 prev를 NULL로 저장
	plist->head = newNode;                                       // 포인터 변수 head가 새 노드 가리키게 한다

	(plist->numOfData)++;
}

int LFirst(List* plist, Data* pdata)                             // 첫 번째 노드의 데이터 조회
{
	if (plist->head == NULL)
		return FALSE;

	plist->cur = plist->head;                                    // cur이 첫 번째 노드를 가리키게 함
	*pdata = plist->cur->data;                                   // cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

int LNext(List* plist, Data* pdata)                              // 두 번째 이후의 노드 데이터 조회
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->cur = plist->cur->next;                               // cur을 오른쪽으로 이동
	*pdata = plist->cur->data;                                   // cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

int LPrevious(List* plist, Data* pdata)                          // LNext의 반대 방향으로 데이터 조회
{
	if (plist->cur->prev == NULL)
		return FALSE;

	plist->cur = plist->cur->prev;                               // cur을 왼쪽으로 이동
	*pdata = plist->cur->data;                                   // cur이 가리키는 노드의 데이터 반환
	return TRUE;
}

int LCount(List* plist);

```

## DBLinkedListMain.cpp
```
#include <stdio.h>
#include "DBLinkedList.h"

int main()
{
	// 양방향 연결 리스트의 생성 및 초기화
	List list;
	int data;
	ListInit(&list);

	// 8개 데이터 저장
	LInsert(&list, 1);  LInsert(&list, 2);
	LInsert(&list, 3);  LInsert(&list, 4);
	LInsert(&list, 5);  LInsert(&list, 6);
	LInsert(&list, 7);  LInsert(&list, 8);

	// 저장된 데이터의 조회
	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		// 오른쪽 노드로 이동하며 데이터 조회
		while (LNext(&list, &data))
			printf("%d ", data);

		// 왼쪽 노드로 이동하며 데이터 조회
		while (LPrevious(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}
	return 0;
}
```
