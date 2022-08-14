#include <stdio.h>

int LSearch(int arr[], int len, int target)
{
	for (int i = 0; i < len; i++)
{
		if (arr[i] == target)                                //target 찾을 시 idx return
			return i;
	}
	return -1;                                               //못 찾을 시 -1 return
}

int main() 
{
	int arr[] = { 1, 4, 6, 15, 27 };                         
	int idx;

	idx = LSearch(arr, sizeof(arr) / sizeof(int), 15);
	if (idx == -1)
		printf("탐색 실패");
	else
		printf("%d 번 째 인덱스 탐색 완료", idx);

}