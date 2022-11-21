## 조건
1. 점심시간 1시간 동안 고객이 15초당 1명씩 1개를 주문을 한다.
2. 치즈버거 : 12초, 불고기버거 : 15초, 더블버거 : 24초
3. 메뉴는 무작위로 고른다.

### HamburgerSim.cpp
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ListBaseQueue.h"

#define CUS_COME_TERM 15                                 // 고객의 주문 간격 : 초 단위

#define CHE_BUR    0                                     // 치즈버거 상수
#define BUL_BUR    1                                     // 불고기버거 상수
#define DUB_BUR    2                                     // 더블버거 상수

#define CHE_TURM   12                                    // 치즈버거 제작 시간 : 초 단위
#define BUL_TURM   15                                    // 불고기버거 제작 시간 : 초 단위
#define DUB_TURM   24                                    // 더블버거 제작 시간 : 초 단위

int main(void)
{
	int makeProc = 0;                                    // 햄버거 제작 진행상황
	int cheOrder = 0, bulOrder = 0, dubOrder = 0;
	int sec;

	Queue que;

	QueueInit(&que);
	srand(time(NULL));

	// 아래 for문의 1회 회전은 1초의 시간 흐름을 의미함.
	for (sec = 0; sec < 3600; sec++)
	{
		if (sec % CUS_COME_TERM == 0)                    // 15초에 1회씩 TURE가 된다.
		{
			switch (rand() % 3)                          // 버거 랜덤 선택
			{
			case CHE_BUR:
				Enqueue(&que, CHE_TURM);
				cheOrder += 1;
				break;
			case BUL_BUR:
				Enqueue(&que, BUL_TURM);
				bulOrder += 1;
				break;
			case DUB_BUR:
				Enqueue(&que, DUB_TURM);
				dubOrder += 1;
				break;
			}
		}
		if (makeProc <= 0 && !QIsEmpty(&que))
			makeProc = Dequeue(&que);                      // 대기실에 나와서 대기한다.

		makeProc--;                                        // makeProc 값이 줄면서 결국 0이 되고, 버거가 완성이 됨.
	}
	printf("Simulation Report! \n");
	printf(" - Cheese burger : %d \n", cheOrder);
	printf(" - Bulgogi burger : %d \n", bulOrder);
	printf(" - Double burger : %d \n", dubOrder);
	printf(" - Waiting room size : %d \n", QUE_LEN);
	return 0;
}
```
