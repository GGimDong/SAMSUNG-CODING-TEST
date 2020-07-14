/*
	문제가 많이 어려웠다. 
	queue에 x,y뿐 아니라, break의 여부에 따라 따로 array를 선언해 주는 개념이 생소함.
	기존의 State까지 고려해야하는 문제가 나올 경우, 아예 3차원 배열로 확장하는 것을 생각해보자.

*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 1000;

struct point {
	int x;
	int y;
	bool is_break = false;
};

int M, N;
int board[MAX][MAX] = { 0, };
char line[MAX];

int dir[4][2] = { {1,0}, {-1,0},{0,1},{0,-1} };

vector<point> v;

int ans = -1;

// 0 이 안 부순 것. 1은 이미 부순 것.
int time_board[MAX][MAX][2] = {0,};
bool visited[MAX][MAX][2] = { false, };

void bfs() {
	queue<point> q;
	int time;
	
	point s;
	s.x = 0;
	s.y = 0;

	visited[0][0][0] = true;
	time_board[0][0][0] = 1;
	q.push(s);
	
	while (!q.empty()) {
		point next = q.front();
		q.pop();
		int x = next.x, y = next.y;
		int was_breaked = (next.is_break)? 1: 0;

		time = time_board[x][y][was_breaked];
		
		if (x == M - 1 && y == N - 1) {
			ans = time_board[M - 1][N - 1][was_breaked];
			return;
		}

		for (int i = 0; i < 4; i++) {
			int dx = dir[i][0], dy = dir[i][1];
			if (x + dx >= 0 && y + dy >= 0 && x + dx < M && y + dy < N) {
				if (board[x + dx][y + dy] == 1 && !next.is_break && time_board[x + dx][y + dy][1]==0 ) {
					point temp;
					temp.x = x + dx;
					temp.y = y + dy;
					temp.is_break = true;
					q.push(temp);

					time_board[temp.x][temp.y][1] = time + 1;
				}
				else if (board[x + dx][y + dy] == 0 && time_board[x + dx][y + dy][was_breaked] == 0) {
					point temp;
					temp.x = x + dx;
					temp.y = y + dy;
					temp.is_break = next.is_break;
					
					q.push(temp);
					time_board[temp.x][temp.y][was_breaked] = time + 1;
				}
			}
		}
	}
}


int main() {
	cin >> M >> N;

	for (int i = 0; i < M; i++) {
		cin >> line;
		for (int j = 0; j < N; j++) 
			board[i][j] = line[j]-'0';	
	}

	bfs();
	cout << ans;
	/*
	cout << endl << endl;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
			cout << time_board[i][j][0];
		cout << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
			cout << time_board[i][j][1];
		cout << endl;
	}
	*/
	return 0;
}