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
// �̷� ������ �ڷ�ǥ���� �����ϱ�. �ұ�Ģ�� ������� ��Ģ�� ���ư��Բ� �������� ���̴�.
int irregularMove[14][6] = {
//������ġ,  1	2	3	4	5	������ �� �����̴� ��...
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
		int pos[5] = {0, 0, 0, 0, 0};	// ���� 1~4����

		for (int i = 0; i < 10; i++) {
			// ���� �����̰� ���� �߰�
			int pos_idx = order[i], delta = value[i], originPos = pos[pos_idx];
			int irregularIdx = -1;
			bool irregular = false;
			
			// �̹� ������ ���� �� ������
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

			// ���� �� ���� 21(����)�� �ƴϰ� ���� ���ϴ� �Ͱ� �ٸ� �����ٰ� 
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