#include <iostream>

using namespace std;

const int MAX = 50;
int T, M, N, K;
int board[MAX][MAX] = {0, };
int a, b;

int dir[4][2] = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};

void clear(int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			board[i][j] = 0;
}

void dfs(int x, int y, int target) {
	board[x][y] = target;
	for (int i = 0; i < 4; i++) {
		int dx = dir[i][0];
		int dy = dir[i][1];
		if (board[x + dx][y + dy] == -1 && x + dx >= 0 && y + dy >= 0 && x + dx < M && y + dy < N)
			dfs(x + dx, y + dy, target);
	}
}


int main() {
	cin >> T;
	for (int i = 0; i < T; i++) {
		int ans = 0;
		cin >> M >> N >> K;
		for (int j = 0; j < K; j++) {
			cin >> a >> b;
			board[a][b] = -1;
		}

		for (int j = 0; j < M; j++)
			for (int k = 0; k < N; k++)
				if (board[j][k] == -1) 
					dfs(j, k, ++ans);
		
		

		if (i != T - 1)
			clear(M, N);
		cout << ans << endl;
	}
	return 0;
}