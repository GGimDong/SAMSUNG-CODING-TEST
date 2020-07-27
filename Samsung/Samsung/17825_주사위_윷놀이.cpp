#include <cstdio>

int arr[50] = {
	  0, 2, 4, 6, 8,
	 10,12,14,16,18,
	 20,22,24,26,28,
	 30,32,34,36,38,
	 40, 0,13,16,19,
	 25,26,27,28,22,
	 24,30,35
};
// 이런 식으로 자료표현이 유용하군. 불규칙을 어거지로 규칙이 돌아가게끔 만들어놓은 셈이다.
int irregularMove[14][6] = {
//원래위치,  1	2	3	4	5	나왔을 때 움직이는 곳...
		{5, 22, 23, 24, 25, 31},
		{10, 29, 30, 25, 31, 32},
		{15, 28, 27, 26, 25, 31},
		{25, 31, 32, 20, 21, 21},

		{22, 23, 24, 25, 31, 32},
		{23, 24, 25, 31, 32, 20},
		{24, 25, 31, 32, 20, 21},
		
		{26, 25, 31, 32, 20, 21},
		{27, 26, 25, 31, 32, 20},
		{28, 27, 26, 25, 31, 32},

		{29, 30, 25, 31, 32, 20},
		{30, 25, 31, 32, 20, 21},
		{31, 32, 20, 21, 21, 21},
		{32, 20, 21, 21, 21, 21}
};

int order[10]; 
int value[10];
int ans = 0;

void getResult(int idx) {
	if (idx >= 10) {
		
		int result = 0;
		int pos[5] = {0, 0, 0, 0, 0};	// 말은 1~4까지

		for (int i = 0; i < 10; i++) {
			// 말을 움직이고 점수 추가
			int pos_idx = order[i], delta = value[i], originPos = pos[pos_idx];
			int irregularIdx = -1;
			bool irregular = false;
			
			// 이미 도착한 말은 못 움직임
			if (originPos == 21) return;

			for (int j = 0; j < 14; j++) {
				if (irregularMove[j][0] == originPos) {
					irregular = true;
					irregularIdx = j;
					break;
				}
			}
			
			int next_pos;

			if (!irregular) { 
				next_pos = originPos + delta; 
				if (next_pos > 21) next_pos = 21;
			}
			else {
				next_pos = irregularMove[irregularIdx][delta];
			}

			// 다음 갈 곳이 21(도착)이 아니고 현재 비교하는 것과 다른 값에다가 
			for (int j = 1; j <= 4; j++) if (j != pos_idx && next_pos != 21 && pos[j] == next_pos) return;
			result += arr[next_pos];
			pos[pos_idx] = next_pos;
		}

		if (ans < result) ans = result;
	}
	else {
		for (int i = 1; i <= 4; i++) {
			order[idx] = i;
			getResult(idx + 1);
		}
	}
}

int main() {
	for (int i = 0; i < 10; i++) scanf("%d", &value[i]);
	getResult(0);
	printf("%d",ans);

	return 0;
}