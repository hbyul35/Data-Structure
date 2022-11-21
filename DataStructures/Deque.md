# Dequeu(Double - ended - queue)
덱은 앞으로도 뒤로도 넣을 수 있고, 뺄 수 있는 자료구조이다.

## 덱 자료구조의 ADT
* void DequeInit(Deque* pdeq);
* int DQIsEmpty(Deque* pdeq);
* void DQAddFirst(Deque* pdeq, Data data);
* void DQAddLast(Deque* pdeq, Data data);
* Data DQRemoveFirst(Deque* pdeq);
* Data DQRemoveLast(Deque* pdeq);
* Data DQGetFirst(Deque* pdeq);
* Data DQGetLast(Deque* pdeq);

<hr/>

### Deque.h
```
#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
	struct _node* prev;
}Node;

typedef struct _dlDeque
{
	Node* head;
	Node* tail;
}DLDeque;

typedef DLDeque Deque;

void DequeInit(Deque* pdeq);
int DQIsEmpty(Deque* pdeq);

void DQAddFirst(Deque* pdeq, Data data);
void DQAddLast(Deque* pdeq, Data data);

Data DQRemoveFirst(Deque* pdeq);
Data DQRemoveLast(Deque* pdeq);
Data DQGetFirst(Deque* pdeq);
Data DQGetLast(Deque* pdeq);

```

### Deque.cpp
```
#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"

void DequeInit(Deque* pdeq)
{
	pdeq->head = NULL;
	pdeq->tail = NULL;
}

int DQIsEmpty(Deque* pdeq)
{
	if (pdeq->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void DQAddFirst(Deque* pdeq, Data data)
{
	Node* newNode = new(Node);
	newNode->data = data;

	newNode->next = pdeq->head;

	if (DQIsEmpty(pdeq))
		pdeq->tail = newNode;
	else
		pdeq->head->prev = newNode;

	newNode->prev = NULL;
	pdeq->head = newNode;
}

void DQAddLast(Deque* pdeq, Data data)
{
	Node* newNode = new(Node);
	newNode->data = data;
	newNode->prev = pdeq->tail;

	if (DQIsEmpty(pdeq))
		pdeq->head = newNode;
	else
		pdeq->tail->next = newNode;

	newNode->next = NULL;
	pdeq->tail = newNode;
}

Data DQRemoveFirst(Deque* pdeq)
{
	Node* rnode = pdeq->head;
	Data rdata;
	if (DQIsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}

	rdata = pdeq->head->data;

	pdeq->head = pdeq->head->next;
	free(rnode);

	if (pdeq->head == NULL)
		pdeq->tail == NULL;
	else
		pdeq->head->prev = NULL;

	return rdata;
}

Data DQRemoveLast(Deque* pdeq)
{
	Node* rnode = pdeq->tail;
	Data rdata;
	if (DQIsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}

	rdata = pdeq->tail->data;

	pdeq->tail = pdeq->tail->prev;
	free(rnode);

	if (pdeq->tail == NULL)
		pdeq->head == NULL;
	else
		pdeq->tail->next = NULL;

	return rdata;
}

Data DQGetFirst(Deque* pdeq)
{
	if (DQIsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	return pdeq->head->data;
}

Data DQGetLast(Deque* pdeq)
{
	if (DQIsEmpty(pdeq))
	{
		printf("Deque Memory Error! \n");
		exit(-1);
	}
	return pdeq->tail->data;
}
```

### DequeMain.cpp
```
#include <stdio.h>
#include "Deque.h"

int main(void)
{
	//Deque의 생성 및 초기화
	Deque deq;
	DequeInit(&deq);

	// 데이터 넣기 1차
	DQAddFirst(&deq, 3);
	DQAddFirst(&deq, 2);
	DQAddFirst(&deq, 1);

	DQAddLast(&deq, 4);
	DQAddLast(&deq, 5);
	DQAddLast(&deq, 6);

	// 데이터 꺼내기
	while (!DQIsEmpty(&deq))
		printf("%d ", DQRemoveFirst(&deq));

	printf("\n");

	// 데이터 넣기 2차
	DQAddFirst(&deq, 3);
	DQAddFirst(&deq, 2);
	DQAddFirst(&deq, 1);

	DQAddLast(&deq, 4);
	DQAddLast(&deq, 5);
	DQAddLast(&deq, 6);

	// 데이터 꺼내기 2차
	while (!DQIsEmpty(&deq))
		printf("%d ", DQRemoveLast(&deq));

	return 0;
	
}
```
