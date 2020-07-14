/*
	배열의 첫 번째 행과 열, 마지막 행과 열에는 항상 0으로 채워진다.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
	int x;
	int y;
	int delta;
};

const int MAX = 300;
int board[MAX][MAX];
int no_ice = 0;
int N, M;
int ans = 0;

int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int visited[MAX][MAX] = { 0, };

int num_of_sea(int x, int y) {
	int num = 0;
	for (int i = 0; i < 4; i++) {
		int dx = dir[i][0], dy = dir[i][1];
		int next_x = dx + x, next_y = dy + y;
		if (board[next_x][next_y] == 0)
			num++;
	}
	return num;
}

void melt() {
	vector<point> q;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] != 0) {
				point p;
				p.x = i;
				p.y = j;
				p.delta = num_of_sea(i, j);
				q.push_back(p);
			}
	
	while (!q.empty()) {
		point next = q.back();
		q.pop_back();
		int x = next.x, y = next.y, delta = next.delta;
		board[x][y] = max(0, board[x][y] - delta);
	}
}

void dfs(int x, int y, int idx, int (*visited)[MAX]) {
	visited[x][y] = idx;
	for (int i = 0; i < 4; i++) {
		int dx = dir[i][0], dy = dir[i][1];
		int next_x = dx + x, next_y = dy + y;
		if(board[next_x][next_y] != 0 && visited[next_x][next_y] == 0)
			dfs(x + dx, y + dy, idx, visited);
	}
}

int is_divided() {
	int idx = 0;
	int check = 0;

	for (int i = 1; i < N-1; i++)
		for (int j = 1; j < M-1; j++)
			if (board[i][j] != 0 && visited[i][j] == 0) {
				check = 1;
				idx++;
				if (idx == 2)
					return 1;
				dfs(i, j, idx, visited);
			}

	if (check == 0)
		no_ice = 1;

	return 0;
}

void clear() {
	for (int i = 1; i < N-1; i++)
		for (int j = 1; j < M-1; j++)
			visited[i][j] = 0;
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> board[i][j];

	
	do{
		if (is_divided() == 1)
			break;
		melt();
		ans++;
		clear();
	}while (no_ice == 0);

	if (no_ice == 1)
		ans = 0;

	cout << ans;
	return 0;
}