/*
	DFS를 사용하였더니 시간초과가 남. 
	모든 경우의 수가 끝날 때 까지 기다렸기 때문
	BFS를 사용하면, 매 step별로 검사하고 사실 가장 빠른 길로 도달할 수 있으면서 끝낼 수 있기 때문에
	이를 사용해야 하는 문제였음.
	2차원에 대한 얘기니까 2차원구조가 필요한 것 같다.
*/

#include <iostream>
#include <queue>
using namespace std;

struct point {
	int x;
	int y;
};

const int MAX = 100;

char line[MAX];
int board[MAX][MAX] = { 0, };

int M, N;
int ans;

int dir[4][2] = {
	{1,0},
	{-1,0},
	{0,1},
	{0,-1}
};


void print_board() {

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
			cout << board[i][j];
		cout << endl;
	}
}

/*
	1. 기준점에서 4방향을 검사
	2. 갈 수 있는 곳을 queue에 넣음
	3. pop하면서 다음 지점에서 갈 수 있는 곳을 push하는데 이 때 step을 1씩 추가
*/
void bfs(int x, int y) {
	queue<point> q;
	bool visited[MAX][MAX] = { false, };
	int step = 1;

	board[x][y] = step;
	point s;
	s.x = x;
	s.y = y;
	q.push(s);
	
	while (!q.empty()) {
		point next = q.front();
		q.pop();
		step = board[next.x][next.y];

		for (int i = 0; i < 4; i++) {
			int dx = dir[i][0], dy = dir[i][1];
			if (!visited[next.x + dx][next.y + dy] && board[next.x + dx][next.y + dy] == -1 && next.x + dx >= 0 && next.y + dy >= 0 && next.x + dx < M && next.y + dy < N) {
				point temp;
				temp.x = next.x + dx;
				temp.y = next.y + dy;
				q.push(temp);
				visited[temp.x][temp.y] = true;
				board[temp.x][temp.y] = step+1;
			}
		}
	} 
}

int main() {
	cin >> M >> N;
	for (int i = 0; i < M; i++) {
		cin >> line;
		for (int j = 0; j < N; j++) {
			if (line[j] == '1')
				board[i][j] = -1;
		}
	}
	
	bfs(0, 0);

	cout << board[M-1][N-1];
	return 0;
}