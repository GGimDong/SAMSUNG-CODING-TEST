#include <iostream>

using namespace std;

int dir[5][2] = { {0,0}, {0,1}, {0,-1}, {-1,0}, {1,0} };
int board[15][15][5]; // 0�� color, 1~4������ order
int N, K;

struct Pieces {
	int x, y, d;

	void changeDir() {
		if (d == 1) d = 2;
		else if (d == 2) d = 1;
		else if (d == 3) d = 4;
		else if (d == 4) d = 3;
	}
}pieces[11];

bool checkInside(int x, int y) {
	if (x <= 0 || y <= 0 || x > N || y > N) return false;
	return true;
}

bool movePiece(int idx) {
	int x = pieces[idx].x, y = pieces[idx].y,d = pieces[idx].d;
	
	// �� �Ʒ��� �ƴϸ� �� ������.
	if (idx != board[x][y][1]) return false;

	int nx = x + dir[d][0], ny = y + dir[d][1];
	int color = board[nx][ny][0];

	// �Ķ����̰ų� ���� ���ϴ� ���̸� �ڷ� ���� �� �κ� �ٽ� ������Ʈ
	if (!checkInside(nx, ny) || color == 2) {
		pieces[idx].changeDir();
		d = pieces[idx].d;
		nx = x + dir[d][0], ny = y + dir[d][1];
		color = board[nx][ny][0];
	}
	
	// �׷����� �� ���� �����̸� ����, �ƴ� ��� ��ǻ� ���� �Ʒ� �ڵ�� �׳� �������� �κ�
	if (!checkInside(nx, ny) || color == 2) return false;
	

	if (color == 1) { // ���� �ٲٱ�
		int t[4] = { 0, };
		for (int i = 1; i <= 4; i++) t[4 - i] = board[x][y][i];
		int t_idx = 1;
		for (int i = 0; i < 4; i++) {
			if (t[i] == 0) continue;
			board[x][y][t_idx++] = t[i];
		}
	}

	int index = 1;
	for (int i = 1; i <= 4; i++) {
		if (board[nx][ny][i] != 0) continue;
		int value = board[x][y][index];
		board[x][y][index] = 0;
		board[nx][ny][i] = value;
		pieces[value].x = nx, pieces[value].y = ny;
		index++;
	}

	if (board[nx][ny][4] != 0) return true;

	return false;
}

int main() {
	bool is_finished = false;
	int ans = -1;
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> board[i][j][0];

	for (int i = 1; i <= K; i++) {
		cin >> pieces[i].x >> pieces[i].y >> pieces[i].d;
		board[pieces[i].x][pieces[i].y][1] = i;
	}

	for (int time = 1; time <= 1000; time++) {
		for (int i = 1; i <= K; i++) {
			if (movePiece(i)) {
				is_finished = true;
				break;
			}
		}
		if (is_finished) {
			ans = time;
			break;
		}
	}

	cout << ans;
	return 0;
}