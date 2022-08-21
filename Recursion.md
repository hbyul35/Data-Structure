# Recursion

재귀함수는 함수 안에 함수를 넣어 함수가 호출되면 해당 함수의 복사본을 만들어 실행하는 구조이다.
```
void Recursive(int num)
{
	if (num <= 0) return;                      //입력 파라미터가 0이하이면 재귀 탈출
	printf("Recursive Call %d \n", num);       //확인을 위한 출력
	Recursive(num - 1);                        //재귀함수 호출
}

int main()
{
	Recursive(3);
	return 0;
}
```

## RecursiveFactorial
팩토리얼 : n! = n x (n-1) x (n-2) . . . x 2 x 1
```
int RecursiveFactorial(int num)
{
	if (num == 0) return 1;                                   //입력파라미터가 1이면 1 반환
	else return num* RecursiveFactorial(num - 1);             //팩토리얼을 위한 -1 재귀 함수 호출
}

int main()
{
	int num;
	scanf_s("%d", &num);                                       
	printf("%d! = %d \n", num, RecursiveFactorial(num));
	return 0;
}
```
## Fibonacci
피보나치 수열 : n = n-1 + n-2

```
int Fibonacci(int num)
{
	if (num == 1) return 0;                                       //피보나치 수열의 1값은 0으로 고정
	else if (num == 2) return 1;                                  //피보나치 수열의 2값은 1로 고정
	else return Fibonacci(num - 1) + Fibonacci(num - 2);          //n = n-1 + n-2
}

int main()
{
	int num;
	scanf_s("%d", &num);
	for ( int i = 1; i < num; i++)
		printf("%d \n", Fibonacci(i));
	return 0;
}
```

## RecursiveBinarySearch
재귀를 이용한 이진탐색 알고리즘
```
int RecursiveBinarySearch(int arr[],int first, int last, int target)
{
	int mid;

	if (first > last) return -1;

	mid = (first + last) / 2;
	
	if (arr[mid] == target)                                               //mid가 타겟이면 인덱스 반환
		return mid;
	else if (target < arr[mid] )                                           //타겟이 mid보다 앞에 있을 경우
		return RecursiveBinarySearch(arr, first, mid - 1, target);         //마지막값을 변경하여 재탐색
	else                                                                  //타겟이 mid보다 뒤에 있을 경우
		return RecursiveBinarySearch(arr, mid + 1, last, target);        //초기값을 변경하여 재탐색
}

int main()
{
	int arr[] = { 1,4,17,42,94 };
	int idx;

	idx = RecursiveBinarySearch(arr, 0, sizeof(arr) / sizeof(int)-1, 42);
	if (idx == -1)
		printf("탐색을 실패했습니다.");
	else
		printf("%d 번 째에서 발견했습니다.",idx);
	return 0;
}
```

## 하노이타워
```
int HanoiTower(int num, char from, char by, char to)
{
	if (num ==1)
		printf("원반을 %c 에서 %c로 이동했습니다.", from, to);

	else
	{
		HanoiTower(num - 1, from, to, by);
		printf("%d를 %c 에서 %c로 이동했습니다.", num, from, to);
		HanoiTower(num - 1, by, from, to);
	}
}

int main()
{
	HanoiTower(3, 'A', 'B', 'C');
	return 0;
}
```

