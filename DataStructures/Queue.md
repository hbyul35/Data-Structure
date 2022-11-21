# Queue(큐)
먼저 들어간 것이 먼저 나오는 '선입선출' 방식의 자료구조이다. 
FIFO(First-In, First-Out) 자료구조라고도 불린다.

## ADT 정의
* void QueueInit(Queue * pq);                    // 큐의 초기화
* int QIsEmpty(Queue * pq);                      // 큐가 빈 경우 TRUE, 아닌경우 FALSE 반환
* void Enqueue(Queue * pq, Data data);           // 스택에 데이터 저장
* Data Dequeue(Queue * pq);                      // 마지막 요소 삭제 및 반환
* Data QPeek(Queue * pq);                        // 마지막 요소 삭제하지않고 반환

<hr/>

# 큐의 배열 기반 구현

### CircularQueue.h
```
#define QUE_LEN 100
#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _cQueue
{
	int front;
	int rear;
	Data queArr[QUE_LEN];
} CQueue;

typedef CQueue Queue;

void QueueInit(Queue* pq);
int QIsEmpty(Queue* pq);

void Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data QPeek(Queue* pq);

```

### CircularQueue.cpp
```
#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"

void QueueInit(Queue* pq)                            // 텅 빈 경우 front 와 rear은 동일위치 가리킴
{
	pq->front = 0;
	pq->rear = 0;
}

int QIsEmpty(Queue* pq)
{
	if (pq->front == pq->rear)                      // 큐가 비었다면,
		return TRUE;
	else
		return FALSE;
}

int NextPosIdx(int pos)                              // 큐의 다음 위치에 해당하는 값의 인덱스 값 반환
{
	if (pos == QUE_LEN - 1)                          // 배열의 마지막 요소의 인덱스 값이라면
		return 0;
	else
		return pos + 1;
}

void Enqueue(Queue* pq, Data data)
{
	if (NextPosIdx(pq->rear) == pq->front)            // 큐가 꽉 찼다면,
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->rear = NextPosIdx(pq->rear);                   // rear을 한 칸 이동
	pq->queArr[pq->rear] = data;                       // front가 가리키는 데이터 반환
}

Data Dequeue(Queue* pq)
{
	if (NextPosIdx(pq->rear) == pq->front)            // 큐가 꽉 찼다면,
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);                 // front를 한 칸 이동
	return pq->queArr[pq->front];                      // front가 가리키는 데이터 반환
}

Data QPeek(Queue* pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	return pq->queArr[NextPosIdx(pq->front)];
}

```

### CircularQueueMain.cpp

```
#include <stdio.h>
#include "CircularQueue.h"

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
