#include <stdio.h>

int LSearch(int arr[], int len, int target)
{
	for (int i = 0; i < len; i++)
{
		if (arr[i] == target)                                //target ã�� �� idx return
			return i;
	}
	return -1;                                               //�� ã�� �� -1 return
}

int main() 
{
	int arr[] = { 1, 4, 6, 15, 27 };                         
	int idx;

	idx = LSearch(arr, sizeof(arr) / sizeof(int), 15);
	if (idx == -1)
		printf("Ž�� ����");
	else
		printf("%d �� ° �ε��� Ž�� �Ϸ�", idx);

}