#include <stdio.h>

int BSearch(int arr[], int len, int target)
{
	int first = 0;
	int last = len -1 ;
	int mid;

	while (first < last)
	{
		mid = (first + last)/2;                          //중간지점

		if (arr[mid] == target)                          //목표를 찾을 경우
			return mid;
		else
		{
			if (target > arr[mid])                       //목표가 중간보다 클 경우
				first = mid+1;
			else                                         //목표가 중간보다 작을 경우
				last = mid-1;
		}
		return -1;
	}
}

int main()
{
	int arr[] = { 1, 2, 9, 15, 26 };
	int idx;
	
	idx = BSearch(arr, sizeof(arr) / sizeof(int), 3);

	if (idx == -1)
		printf("탐색 실패");
	else
		printf("%d 번째 탐색 완료", idx);

	return 0;
}