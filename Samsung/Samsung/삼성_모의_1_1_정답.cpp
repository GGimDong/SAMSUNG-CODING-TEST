/*
	��Ģ�� ������ ������, ���� ������ ���� �ھ� �־�� ���� ���� ����. 
	�׷��� �ص�, ��ǻ� 5�� �� �Ѿ�ϱ� ���� ���� �׳� �־ ����.
*/
#include <cstdio>

int arr[35] = {
	0, 5, 10 ,15 ,20,
	50, 30, 35, 40, 45,
	100, 55, 60, 65, 70,
	75, 80, 85, 90, 95,
	500, 1000, 275, 250, 300,
	150, 175, 150, 125, 350, 400
};

int moving[35][6];	// moving[x][y]: x�� �ִµ� y����ŭ �̵��� ���� �����̸� �ǳ�?

// moving�� �־��ֱ� ���ϰ� �ϱ� ���� ���� ��. �������� �߿�� �ؾ� �Ѵ�!
int temp[15][6] = {
	{5, 22, 23, 24, 25, 26},
	{10, 27, 28, 24, 29, 30},
	{22, 23, 24 ,25 ,26, 15},
	{23, 24, 25, 26, 15, 16},
	{24, 29, 30, 20, 21, 21},
	{25, 26, 15, 16, 17, 18},
	{26, 15, 16, 17, 18, 19},
	{27, 28, 24, 29, 30, 20},
	{28, 24, 29, 30, 20 ,21},
	{29, 30, 20, 21, 21, 21} ,
	{30, 20, 21, 21, 21, 21}
};

int current[5];
int data[15], who[15];
int maxScore;

int runThisGame() {
	int result = 0;

	for (int i = 1; i <= 4; i++) current[i] = 0;

	for (int i = 0; i < 10; i++) {
		int d = data[i], w = who[i]; // d��ŭ w�� �����δ�.
		if (current[w] == 21) return -1;
		bool flag = false;

		for (int j = 0; j < 11; j++) {
			if (current[w] == temp[j][0]) {
				flag = true;	// �Ϲ� ��Ģ���� Ư�� ��Ģ������ �˷���
				break;
			}
		}

		if (flag) {
			current[w] = moving[current[w]][d];
		}
		else {
			current[w] += d;
			if (current[w] >= 21) current[w] = 21;
		}

		// ���� ��ġ�� �����̹Ƿ� �̸� �˻�
		if (current[w] == 21) continue;
		for (int j = 1; j <= 4; j++) {
			if (w != j && current[w] == current[j]) return -1;
		}
	}

	for (int i = 1; i <= 4; i++) result += arr[current[i]];
	
	return result;
}

void getResult(int idx) {
	if (idx >= 10) {
		int value = runThisGame();
		if (value > maxScore) maxScore = value;
	}
	else {
		for (int i = 1; i <= 4; i++) {
			who[idx] = i;
			getResult(idx + 1);
		}
	}
}

int main() {
	for (int i = 0; i < 11; i++) {
		for (int j = 1; j <= 5; j++) {
			moving[temp[i][0]][j] = temp[i][j];
		}
	}

	int t;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		for (int j = 0; j < 10; j++) scanf("%d", &data[j]);
		maxScore = -9999999;
		getResult(0);

		printf("#%d %d\n", i+1, maxScore);
	}

	return 0;
}