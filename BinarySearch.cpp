#include <stdio.h>

int BSearch(int arr[], int len, int target)
{
	int first = 0;
	int last = len -1 ;
	int mid;

	while (first < last)
	{
		mid = (first + last)/2;                          //�߰�����

		if (arr[mid] == target)                          //��ǥ�� ã�� ���
			return mid;
		else
		{
			if (target > arr[mid])                       //��ǥ�� �߰����� Ŭ ���
				first = mid+1;
			else                                         //��ǥ�� �߰����� ���� ���
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
		printf("Ž�� ����");
	else
		printf("%d ��° Ž�� �Ϸ�", idx);

	return 0;
}