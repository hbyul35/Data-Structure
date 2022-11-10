## 시간 복잡도(Time Complexity)
**속도**에 해당하는 알고리즘의 수행시간 분석결과

## 공간 복잡도(Space Complexity)
**메모리의 사용량**에 해당하는 알고리즘의 수행시간 분석결과

<hr/>

### 수행시간 측정 방법
연산의 횟수를 센다.
- 처리해야 할 데잍의 수 n에 대한 연산횟수의 함수 T(n)을 구성한다.
- == 연산을 적게 수행하는 것이 좋은 알고리즘이다.
- 최선의 경우(best case)와 최악의 경우(worst case), 평균적인 경우(average case)가 있고, 평가에는 보통 **최악의 경우**가 선택된다.

## 순차 탐색(Linear Search) 알고리즘과 시간 복잡도 분석
```
#include <stdio.h>

int LSearch(int arr[], int len, int target)
{
	for (int i = 0; i < len; i++)
{
		if (arr[i] == target)                                  //target 찾을 시 idx return
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
	
	return 0;
}
```

* 최악의 경우
  * T(n)
  
* 평균적인 경우
  * 탐색 대상이 존재하지 않는 경우의 연산횟수 : n
  * 탐색 대상이 존재하는 경우의 연산횟수 : n/2
  * 이 둘을 하나의 식으로 묶을 경우 : n * 1/2 + n/2 * 1/2 = 3/4n

