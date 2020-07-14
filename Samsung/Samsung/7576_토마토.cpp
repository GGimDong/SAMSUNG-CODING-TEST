#include <iostream>
#include <queue>

using namespace std;

const int MAX = 1000;

struct point {
	int x;
	int y;
};

int dir[4][2] = { 
	{1,0},
	{-1,0},
	{0,1},
	{0,-1} 
};

queue<point> q;
int board[MAX][MAX] = {0, };
int M, N;
int time = 1;

bool is_finished() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] == 0)
				return false;

	return true;
}

void bfs() {
	while (!q.empty()) {
		point next = q.front();
		q.pop();
		int x = next.x, y = next.y;
		time = board[x][y];
		
		for (int i = 0; i < 4; i++) {
			int dx = dir[i][0], dy = dir[i][1];
			if (board[x + dx][y + dy] == 0 && x + dx >= 0 && y + dy >= 0 && x + dx < N && y + dy < M) {
				point temp;
				temp.x = x + dx;
				temp.y = y + dy;
				q.push(temp);
				board[x + dx][y + dy] = time + 1;
			}
		}
	}
}

int main() {
	cin >> M >> N;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 1) {
				point temp;
				temp.x = i;
				temp.y = j;
				q.push(temp);
			}
		}

	bfs();

	if (is_finished())
		cout << time-1;
	else
		cout << "-1";

	return 0;
}