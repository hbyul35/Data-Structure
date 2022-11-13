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
