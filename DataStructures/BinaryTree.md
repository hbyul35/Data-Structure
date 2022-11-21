## BinaryTree.h
```
typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
}BTreeNode;

// 트리를 표현한 구조체를 정의하지 않은 이유는 공집합 노드 때문이다.

BTreeNode* MakeBTreeNode(void);                                    // 노드의 생성
BTData GetData(BTreeNode* bt);                                     // 노드에 저장된 데잍를 반환
void SetData(BTreeNode* bt, BTData data);                          // 노드에 데이터를 저장

BTreeNode* GetLeftSubTree(BTreeNode* bt);                          // 왼쪽 서브 트리 주소 값 반환
BTreeNode* GetRightSubTree(BTreeNode* bt);                         // 오른쪽 서브 트리 주소 값 반환

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub);             // 노드 A의 왼쪽 자식 노드로 노드 B 연결
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub);            //노드 A의 오른쪽 자식 노드로 노드 C 연결
```

## BinaryTree.cpp
```
#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

BTreeNode* MakeBTreeNode(void)
{
	BTreeNode* nd = new(BTreeNode);
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

BTData GetData(BTreeNode* bt)
{
	return bt->data;
}

void SetData(BTreeNode* bt, BTData data)
{
	bt->data = data;
}

BTreeNode* GetLeftSubTree(BTreeNode* bt)
{
	return bt->left;
}

BTreeNode* GetRightSubTree(BTreeNode* bt)
{
	return bt->right;
}

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->left != NULL)
		free(main->left);

	main->left = sub;
}

void MakeRightSubTree(BTreeNode* main, BTreeNode* sub)
{
	if (main->right != NULL)
		free(main->right);

	main->right = sub;
}
```
