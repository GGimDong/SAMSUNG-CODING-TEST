#include <cstdio>

const int MAX = 15;

int n, m, k, t;
int myMap[MAX][MAX];

int dirY[4] = {-1,0,1,0};
int dirX[4] = {0,1,0,-1};

int dir[6][4] = {
//	상우하좌
	{0,0,0,0},
	{1,0,0,0},
	{1,0,1,0},
	{1,1,0,0},
	{1,1,0,1},
	{1,1,1,1}
};
int rotates[MAX];
int valCnt;
int result;

void opening(int y, int x, int rotate) {
	int valIndex = myMap[y][x];
	int myDir[4] = { 0, };
	int myValue = 0;
	
	for (int i = 0; i < 4; i++) myDir[i] = dir[valIndex][i];

	for (int i = 0; i < rotate; i++) {
		int temp = myDir[3];
		// 여기부터다시하세요
	}


}

void getResult(int idx) {
	if (idx >= valCnt) {
		int myValIdx = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				opening(i, j, rotates[myValIdx++]);
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			rotates[idx] = i;
			getResult(idx + 1);
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);

	for (int testcase = 0; testcase < t; testcase++) {
		scanf("%d %d", &n, &m);
		
		valCnt = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &myMap[i][j]);
				if (myMap[i][j] >= 1 && myMap[i][j] <= 5) valCnt++;
			}
		}

		getResult(0);
		printf("#%d %d\n", testcase + 1, result);
	}

	return 0;
}