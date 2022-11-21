### ListBaseQueue.h
```
#define QUE_LEN 100
#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
} Node;

typedef struct _LQueue
{
	Node* front;
	Node* rear;
} LQueue;

typedef LQueue Queue;

void QueueInit(Queue* pq);
int QIsEmpty(Queue* pq);

void Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data QPeek(Queue* pq);

```

### ListBaseQueue.cpp
```
#include <stdio.h>
#include <stdlib.h>
#include "ListBaseQueue.h"

void QueueInit(Queue* pq)                            // 텅 빈 경우 front 와 rear은 동일위치 가리킴
{
	pq->front = NULL;
	pq->rear = NULL;
}

int QIsEmpty(Queue* pq)
{
	if (pq->front == NULL)                           // F에 NULL이 저장되어 있으면,
		return TRUE;
	else
		return FALSE;
}

void Enqueue(Queue* pq, Data data)
{
	Node* newNode = new(Node);
	newNode->next = NULL;
	newNode->data = data;

	if (QIsEmpty(pq))                                 // 첫 노드의 추가라면,
	{
		pq->front = newNode;                          // front가 새 노드를 가리키게 하고,
		pq->rear = newNode;                           // rear도 새 노드를 가리키게 한다.
	}
	else                                              // 두 번째 이후의 노드 추가라면,
	{
		pq->rear->next = newNode;                     // 마지막 노드가 새 노드를 가리키게 하고,
		pq->rear = newNode;                           // rear가 새 노드를 가리키게 한다.
	}
}

Data Dequeue(Queue* pq)
{
	Node* delNode;
	Data retData;

	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	delNode = pq->front;                                // 삭제할 노드의 주소 값 저장
	retData = delNode->data;                            // 삭제할 노드가 지닌 값 저장
	pq->front = pq->front->next;                        // 삭제할 노드의 다음 노드를 front가 가리킴

	free(delNode);
	return retData;
}

Data QPeek(Queue* pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	return pq->front->data;
}

```

### ListBaseQueueMain.cpp
```

#include <stdio.h>
#include "ListBaseQueue.h"

int main(void)
{
	//Quueue의 생성 및 초기화
	Queue q;
	QueueInit(&q);

	// 데이터 넣기
	Enqueue(&q, 1);  Enqueue(&q, 2);
	Enqueue(&q, 3);  Enqueue(&q, 4);
	Enqueue(&q, 5);

	// 데이터 꺼내기
	while (!QIsEmpty(&q))
		printf("&d", Dequeue(&q));

	return 0;
}
```
