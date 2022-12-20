# 수식 트리
이진 트리를 이용해서 수식을 표현해 놓은 것

1. BinaryTree2 
2. ListBaseStack

네 개의 파일들을 활용한다.
이때, ListBaseStack.h 에 아래를 변경해준다.
```
typedef BTreeNode* Data;
``` 

</hr>


### ExpressionTree.h
```
#include "BinaryTree2.h"

BTreeNode* MakeExpTree(char exp[]);           // 수식 트리 구성
int EvaluateExpTree(BTreeNode* bt);           // 수식 트리 계산

void ShowPrefixTypeExp(BTreeNode* bt);        // 전위 표기법 기반 출력
void ShowInfixTypeExp(BTreeNode* bt);        // 중위 표기법 기반 출력
void ShowPostfixTypeExp(BTreeNode* bt);      // 후위 표기법 기반 출력
```

### ExpressionTree.cpp
```
#include "BinaryTree2.h"
#include "ListBaseStack.h"
#include <string.h>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>


BTreeNode* MakeExpTree(char exp[])
{
	Stack stack;
	BTreeNode* pnode;

	int explen = strlen(exp);
	int i;

	StackInit(&stack);

	for ( i = 0; i < explen; i++)
	{
		pnode = MakeBTreeNode();

		if (isdigit(exp[i]))                             // 피연산자라면
		{
			SetData(pnode, exp[i] - '0');                // 문자를 정수로 바꿔서 저장
		}
		else
		{
			MakeRightSubTree(pnode, SPop(&stack));
			MakeLeftSubTree(pnode, SPop(&stack));
			SetData(pnode, exp[i]);
		}

		SPush(&stack, pnode);
	}
	return SPop(&stack);
}

int EvaluateExpTree(BTreeNode* bt)
{

}

void ShowNodeData(int data)
{
	if (0 <= data && data <= 9)
		printf("%d ", data);
	else
		printf("%c ", data);
}

void ShowPrefixTypeExp(BTreeNode* bt)
{
	PreorderTraversal(bt, ShowNodeData);
}

void ShowInfixTypeExp(BTreeNode* bt)
{
	InorderTraversal(bt, ShowNodeData);
}

void ShowPostfixTypeExp(BTreeNode* bt)
{
	PostorderTraversal(bt, ShowNodeData);
}
```

### ExpressionTreeMain.cpp
```
#include <stdio.h>
#include "ExpressionTree.h"

int main(void)
{
	char exp[] = "12+7*";
	BTreeNode* eTree = MakeBTreeNode();

	printf(" 전위 표기법의 수식: ");
	ShowPrefixTypeExp(eTree); printf("\n");

	printf(" 중위 표기법의 수식: ");
	ShowInfixTypeExp(eTree); printf("\n");

	printf(" 후위 표기법의 수식: ");
	ShowPostfixTypeExp(eTree); printf("\n");

	printf("연산의 결과: %d \n", EvaluateExpTree(eTree));

	return 0;
}
```

// 오류 못고침 흐아아아아아아아ㅏ아아아ㅏ아아아아아아앙아앙 오류가 세상에서 ㅓ제ㅣㅇㄹ 싫 어 !!! 언젠간 고치겠지
