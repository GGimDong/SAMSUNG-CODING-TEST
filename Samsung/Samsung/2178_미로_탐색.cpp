/*
	DFS�� ����Ͽ����� �ð��ʰ��� ��. 
	��� ����� ���� ���� �� ���� ��ٷȱ� ����
	BFS�� ����ϸ�, �� step���� �˻��ϰ� ��� ���� ���� ��� ������ �� �����鼭 ���� �� �ֱ� ������
	�̸� ����ؾ� �ϴ� ��������.
	2������ ���� ���ϱ� 2���������� �ʿ��� �� ����.
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
	1. ���������� 4������ �˻�
	2. �� �� �ִ� ���� queue�� ����
	3. pop�ϸ鼭 ���� �������� �� �� �ִ� ���� push�ϴµ� �� �� step�� 1�� �߰�
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