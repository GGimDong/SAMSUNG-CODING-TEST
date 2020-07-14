#include <iostream>
#include <queue>

using namespace std;

const int MAX = 100;

struct point {
	int x;
	int y;
	int z;
};

int dir[6][3] = {
	{1,0,0},
	{-1,0,0},
	{0,1,0},
	{0,-1,0},
	{0,0,1},
	{0,0,-1}
};

queue<point> q;
int board[MAX][MAX][MAX] = { 0, };
int M, N, H;
int time = 1;

bool is_finished() {
	for (int i = 0; i < H; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < M; k++)
				if (board[i][j][k] == 0)
					return false;

	return true;
}


void bfs() {
	while (!q.empty()) {
		point next = q.front();
		q.pop();
		int x = next.x, y = next.y, z = next.z;
		time = board[x][y][z];
		
		for (int i = 0; i < 6; i++) {
			int dx = dir[i][0], dy = dir[i][1], dz = dir[i][2];
			
			if(x + dx >= 0 && y + dy >= 0 && z + dz >= 0 && x + dx < H && y + dy < N && z + dz < M&& board[x + dx][y + dy][z + dz] == 0)
			{
					point temp;
					temp.x = x + dx;
					temp.y = y + dy;
					temp.z = z + dz;
					q.push(temp);
					board[x + dx][y + dy][z + dz] = time + 1;
				}
		}
	}
}

int main() {
	cin >> M >> N >> H;

	for (int i = 0; i < H; i++)
		for (int j = 0; j < N; j++) 
			for (int k = 0; k < M; k++) {
			cin >> board[i][j][k];
			if (board[i][j][k] == 1) {
				point temp;
				temp.x = i;
				temp.y = j;
				temp.z = k;
				q.push(temp);
			}
		}

	
	bfs();
	
	if (is_finished())
		cout << time - 1;
	else
		cout << "-1";

	return 0;
}