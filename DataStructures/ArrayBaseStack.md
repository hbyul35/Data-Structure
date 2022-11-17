# Stack
나중에 들어간 것이 먼저 나오는 '후입선출' 방식의 자료구조이다. 
LIFO(Last-In, First-Out) 자료구조라고도 불린다.

## ADT 정의
* void StackInit(Stack * pstack);                // 스택의 초기화
* int SIsEmpty(Stack * pstack);                  // 스택이 빈 경우 TRUE, 아닌경우 FALSE 반환
* void SPush(Stack * pstack, Data data);         // 스택에 데이터 저장
* Data SPop(Stack * pstack);                     // 마지막 요소 삭제 및 반환
* Data SPeek(Stack * pstack);                    // 마지막 요소 삭제하지않고 반환

## ArrayBaseStack.h
```
#define TRUE        1
#define FALSE       0
#define STACK_LEN   100

typedef int Data;

typedef struct _arrayStack
{
	Data stackArr[STACK_LEN];
	int topindex;
} ArrayStack;

typedef ArrayStack Stack;

void StackInit(Stack* pstack);                // 스택의 초기화
int SIsEmpty(Stack* pstack);                  // 스택이 비었는지 확인

void SPush(Stack* pstack, Data data);         // 스택의 push 연산
Data SPop(Stack* pstack);                     // 스택의 pop 연산
Data SPeek(Stack* pstack);                    // 스택의 peek 연산

```

## ArrayBaseStack.cpp
```
#include <stdio.h>
#include <stdlib.h>
#include "ArrayBaseStack.h"

void StackInit(Stack* pstack)
{
	pstack->topindex = -1;                           // 인덱스 위치이기 때문에 -1이 빈 상태
}

int SIsEmpty(Stack* pstack)
{
	if (pstack->topindex == -1)
		return TRUE;                                 // 스택이 비어있다면
	else
		return FALSE;
}

void SPush(Stack* pstack, Data data)
{
	pstack->topindex += 1;                           // 데이터 추가를 위한 인덱스 값 증가
	pstack->stackArr[pstack->topindex] = data;       // 데이터 저장
}

Data SPop(Stack* pstack)
{
	int ridx;

	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	ridx = pstack->topindex;                         // 삭제할 데이터가 저장된 인덱스 값 저장
	pstack->topindex -= 1;                           // pop 연산의 결과로 topIndex 값 하나 감소

	return pstack->stackArr[ridx];                   // 삭제되는 데이터 반환
}

Data SPeek(Stack* pstack)
{
	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	return pstack->stackArr[pstack->topindex];       // 맨 위에 저장된 데이터 반환
}
```

## ArrayBaseStackMain.cpp
```
#include <stdio.h>
#include "ArrayBaseStack.h"

int main(void)
{
	// 스택의 초기화
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
