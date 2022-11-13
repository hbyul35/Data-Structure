## ListBaseStack.h
```
#define         TRUE 1
#define         FALSE 0

typedef int Data;

typedef struct _node                               // 연결 리스트의 노드를 표현한 구조체
{
	Data data;
	struct _node* next;
}Node;
 
typedef struct _listStack                          // 연결 리스트 기반 스택을 표현한 구조체
{
	Node* head;
}ListStack;

typedef ListStack Stack;

void StackInit(Stack* pstack);                // 스택의 초기화
int SIsEmpty(Stack* pstack);                  // 스택이 비었는지 확인

void SPush(Stack* pstack, Data data);         // 스택의 push 연산
Data SPop(Stack* pstack);                     // 스택의 pop 연산
Data SPeek(Stack* pstack);                    // 스택의 peek 연산
```

## ListBaseStack.cpp
```
#include <stdio.h>
#include <stdlib.h>
#include "ListBaseStack.h"

void StackInit(Stack* pstack)
{
	pstack->head = NULL;                       // 포인터 변수 head는 NULL로 초기화한다.
}

int SIsEmpty(Stack* pstack)
{
	if (pstack->head == NULL)                  // 스택이 비었다면 head에 NULL 저장
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack* pstack, Data data)
{ 
	Node* newNode = (Node*)new(Node);          // 새 노드 생성

	newNode->data = data;                      // 새 노드에 데이터 저장
	newNode->next = pstack->head;              // 새 노드가 최근에 추가된 노드를 가리킴

	pstack->head = newNode;                    // 포인터 변수 head가 새 노드를 가리킴
}

Data SPop(Stack* pstack)
{
	Data rdata;
	Node* rnode;

	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	rdata = pstack->head->data;                  // 삭제할 노드의 데이터를 임시로 저장
	rnode = pstack->head;                        // 삭제할 노드의 주소 값을 임시로 저장

	pstack->head = pstack->head->next;           // 삭제할 노드의 다음 노드를 head가 가리킴
	free(rnode);                                 // 노드 삭제
	return rdata;                                // 삭제된 노드의 데이터 반환
}

Data SPeek(Stack* pstack)
{
	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	return pstack->head->data;                     // head가 가리키는 노드에 저장된 데이터 반환
}
```

## ListBaseStackMain.cpp
```
#include <stdio.h>
#include "ListBaseStack.h"

int main(void)
{
	// Stack의 생성 및 초기화
	Stack stack;
	StackInit(&stack);

	// 데이터 넣기
	SPush(&stack, 1); SPush(&stack, 2);
	SPush(&stack, 3); SPush(&stack, 4);
	SPush(&stack, 5);

	//데이터 꺼내기
	while (!SIsEmpty(&stack))
		printf("%d ", SPop(&stack));

	return 0;
}
```
