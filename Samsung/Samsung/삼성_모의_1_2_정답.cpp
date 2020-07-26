#include <cstdio>

const int MAX = 15;

int n, m, k, t;
int myMap[MAX][MAX];

int dirY[4] = {-1,0,1,0};
int dirX[4] = {0,1,0,-1};

int dir[6][4] = {	// valve의종류가 1~5이니까
//	상우하좌
	{0,0,0,0},	// 0번은 안씀
	{1,0,0,0},
	{1,0,1,0},
	{1,1,0,0},
	{1,1,0,1},
	{1,1,1,1}
}; // 각각의 valve가 어느 방향을 쏘면 되는지 
int rotates[MAX];
int valCnt;
int openingValue, result;

void opening(int y, int x, int rotate) {
	int valIndex = myMap[y][x];
	int myDir[4] = { 0, };
	int myValue = 0;
	
	for (int i = 0; i < 4; i++) myDir[i] = dir[valIndex][i];	// 먼저 그 밸프의 방향을

	for (int i = 0; i < rotate; i++) {	// 이제 그 밸브를 돌려야지
		int temp = myDir[3];
		for (int j = 3; j >= 1; j--) myDir[j] = myDir[j - 1];
		myDir[0] = temp;
	}

	for (int i = 0; i < 4; i++) {
		if (myDir[i] == 1) {
			int curY = y;
			int curX = x;

			while (1) {
				curY = curY + dirY[i];
				curX = curX + dirX[i];

				if (!(curY >= 0 && curY < n && curX >= 0 && curX < m)) break;
				
				if (myMap[curY][curX] == 0) {
					myMap[curY][curX] = 8;
					openingValue++;
				}
				else if (myMap[curY][curX] == 6) break;
			}

		}
	}

}

void getResult(int idx) {
	if (idx >= valCnt) {
		int myValIdx = 0;
		openingValue = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				opening(i, j, rotates[myValIdx++]);
			}
		}

		if (openingValue > result) result = openingValue;

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