* 중위 표기법(infix notation)             
``5 + 2 / 7``
* 전위 표기법(prefix notation)         
``+ 5 / 2 7``
* 후위 표기법(postfix notation)   
``5 2 7 / +``

전위 or 후위 표기법의 수식을 사용하면 연산자의 배치 순서에 따랏 연산순서가 결정되기 때문에, 연산자의 우선순위를 알 필요가 없고, 
소괄호에 대한 처리도 불필요하다.

## 중위 표기법을 후위 표기법으로 바꾸는 방법
1. 왼쪽부터 피연산자(숫자)는 바로 후위 표기법으로 변환시킨다.
2. 수식을 만날 경우 스택에 쌓는다.
3. 새 연산자가 스택에 있는 연산자보다 우선순위가 높다면 스택에 추가해준다.
   그렇지않다면 스택에 있는 연산자를 후위 표기로 옮기고, 새 연산자는 스택에 추가해준다.
4. 마지막으로 스택의 연산자를 마지막거부터 차례대로 옮겨준다.
5. 만약 연산자의 우선순위가 같다면 스택의 연산자를 옮기고, 새 연산자를 스택에 쌓아준다. 먼저 등장한 연산자가 우선이기 때문이다.
6. 소괄호가 있을경우, 소괄호가 끝나는 시점에서 연산자들을 모두 옮긴뒤, 다시 후위 표기법으로 바꿔준다. 이때, 소괄호는 반환할 필요가 없다.

<hr/>



# 계산기 헤더파일과 소스파일

## 스택의 활용

### ListBaseStack.h
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

### ListBaseStack.cpp
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
<hr/>

## 후위 표기법의 수식으로 변환

### InfixToPostfix.h
```
void ConvToRPNExp(char exp[]);
```

### InfixToPostfix.cpp
```
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ListBaseStack.h"
#pragma warning(disable:4996)

int GetOpPrec(char op)                             // 연산자의 연산 우선순위 정보를 반환한다.
{
	switch (op)
	{
	case '*':
	case '/':
		return 5;                                  // 가장 높은 연산의 우선순위
	case '+':
	case '-':
		return 3;               
	case'(':
		return 1;                                  // 가장 낮은 연산의 우선순위
	}

	return -1;                                     // 등록되지 않은 연산자
}

int WhoPrecOp(char op1, char op2)                  // 두 연산자의 우선순위를 비교하여 결과 반환하는 함수
{
	int op1Prec = GetOpPrec(op1);
	int op2Prec = GetOpPrec(op2);

	if (op1Prec > op2Prec)
		return 1;
	else if (op1Prec < op2Prec)
		return -1;
	else
		return 0;
}

void ConvToRPNExp(char exp[])                       // 후위 표기법으로 변환시키는 함수
{
	Stack stack;
	int expLen = strlen(exp);
	char* convExp = new char[expLen+1];              // 변환된 수식을 담을 공간 마련

	int i, idx = 0;
	char tok, popOp;

	memset(convExp, 0, sizeof(char) * expLen + 1);   // 할당된 배열을 0으로 초기화    *memset : 특정값으로 메모리를 초기화한다.
	StackInit(&stack);

	for ( i = 0; i < expLen; i++)
	{
		tok = exp[i];                                // exp로 전달된 수식을 한 문자씩 tok에 저장
		if (isdigit(tok))                            // isdigit : 매개변수 char 타입의 내용이 10진수라면 1을 반환
		{
			convExp[idx++] = tok;                    // 숫자라면 배열 convExp에 저장
		}
		else                                         // 숫자가 아니라면(연산자라면)
		{
			switch (tok)
			{
			case '(':                                // 여는 소괄호라면,
				SPush(&stack, tok);                  // 스택에 쌓는다.
				break;

			case ')':                                // 닫는 소괄호라면,
				while (1)                            // 반복해서,
				{
					popOp = SPop(&stack);            // 스택에서 연산자를 꺼내어,
					if (popOp == '(')                // 연산자 (를 만날 때까지,
						break;
					convExp[idx++] = popOp;          // 배열 convExp에 저장한다.
				}
				break;

			case '+': case '-':
			case '*': case '/':
				while (!SIsEmpty(&stack) && WhoPrecOp(SPeek(&stack), tok) >= 0)      // 스택에 연산자 존재 확인후, 연산자가 존재한다면 SPeek으로 잠시 꺼낸뒤에 두 연산자 우선순위 비교
					convExp[idx++] = SPop(&stack);                                   // while로 반복하며 스택에 저장된 연산자가 먼저 연산되어야 하는경우, 스택에서 꺼내 배열에 저장
				SPush(&stack, tok);                                                  // tok에 저장된 연산자가 들어갈 스택의 위치를 찾았으므로 스택에 저장
				break;
			}
		}
	}
	while (!SIsEmpty(&stack))                         // 스택에 남아 있는 모든 연산자를,
		convExp[idx++] = SPop(&stack);                // 배열 convExp로 이동

	strcpy(exp, convExp);                             // 변환된 수식을 exp에 복사하고,
	free(convExp);                                    // convExp는 소멸시킨다.
}
```
<hr/>

## 후위 표기법의 수식을 계산

### PostCalculator.h

### PostCalculator.cpp

<hr/>

## 중위 표기법의 수식을 계산

### InfixCalculator.h

### InfixCalculator.cpp


<hr/>

## main 함수

### InfixCalculatorMain.cpp
```
#include <stdio.h>
#include "InfixToPostfix.h"

int main(void)
{
	char exp1[] = "1+2*3";
	char exp2[] = "(1+2)*3";
	char exp3[] = "((1+2)+3)*(5-2)";

	ConvToRPNExp(exp1);
	ConvToRPNExp(exp2);
	ConvToRPNExp(exp3);

	printf("%s \n", exp1);
	printf("%s \n", exp2);
	printf("%s \n", exp3);
	return 0;
}
```

<hr/>

## 중위 표기법을 후위 표기법으로 바꾸는 방법
1. 
2. 수식을 만날 경우 스택에 쌓는다.
3. 
# 후위표기법 계산기

