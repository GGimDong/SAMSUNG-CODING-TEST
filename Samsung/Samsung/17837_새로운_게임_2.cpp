#include <iostream>

using namespace std;

int N, K;
int board[15][15][5]; // 0 �� color, 1~4�� order, 4���� ���̴� ���� ��ǻ� ������ �����Ƿ� �� �̻� ���� �ʿ䵵 ����!
int dir[5][2] = { {0,0}, {0,1}, {0,-1}, {-1,0}, {1,0} };

struct Piece {
	int x, y, d;

	void changeDir() {
		if (d == 1) d = 2;
		else if (d == 2) d = 1;
		else if (d == 3) d = 4;
		else if (d == 4) d = 3;
	}
}pieces[15];

bool checkInside(int x, int y) {
	if (x == 0 || y == 0 || x == N + 1 || y == N + 1) return false;
	return true;
}

bool movePiece(int idx) {
	int x = pieces[idx].x, y = pieces[idx].y, d = pieces[idx].d;
	int nx = x + dir[d][0], ny = y + dir[d][1], color = board[nx][ny][0];

	/*�����*/ //system("pause");
	/*�����*/ //cout << idx << " (" << x << "," << y << ")" << " �� ";

	if (!checkInside(nx, ny) || color == 2) {	// �Ķ����̰ų� �� ���� ���̸� �ڷ� ���ƾ���.
		/*�����*/ //cout << " back ";
		pieces[idx].changeDir(), d = pieces[idx].d;
		nx = x + dir[d][0], ny = y + dir[d][1], color = board[nx][ny][0];	// �ڷ� ��������, �������� ���� ������ �ٽ� ������Ʈ
	}

	/*�����*/ //cout << " (" << nx << "," << ny << "), Dir:" << d;

	if (!checkInside(nx, ny) || color == 2) {
		/*�����*/ //cout << " can't move!" << endl;;
		return false;	// �ڷ� ���Ƶ� �� ���� �׳� ��
	}
	int level; // order�� ���°������ ���ؾ� ��.
	for (int i = 1; i <= 4; i++) if (board[x][y][i] == idx) level = i;

	/*�����*/ //cout << "���� ��ġ:" << level << endl;

	int t_idx = 0;
	int t[4] = { 0,0,0,0 };	// �ű� �ӽ� �迭
	for (int i = level; i <= 4; i++) {
		int p_idx = board[x][y][i];
		t[t_idx++] = p_idx;
		board[x][y][i] = 0;
		pieces[p_idx].x = nx, pieces[p_idx].y = ny;
	}

	if (color == 1) { // �����̸� �� t�� �ڹٲ��ֱ�
		/*�����*/ //cout << " Order change " << endl;
		int zero_num = 0;
		for (int i = 0; i < 4; i++) if (t[i] == 0) zero_num++;
		if (zero_num == 0) {
			int temp_1 = t[0], temp_2 = t[1];
			t[1] = t[2], t[2] = temp_2;
			t[0] = t[3], t[3] = temp_1;
		}
		else if (zero_num == 1) {
			int temp_1 = t[0];
			t[0] = t[2], t[2] = temp_1;
		}
		else if (zero_num == 2) {
			int temp_1 = t[0];
			t[0] = t[1], t[1] = temp_1;
		}
	}

	/*�����*/ //for (int i = 0; i < 4; i++) cout << t[i] << " "; cout << endl;

	// (x,y) -> (nx, ny) �� �̵�
	t_idx = 0;
	for (int i = 1; i <= 4; i++) {
		if (board[nx][ny][i] != 0) continue;	// 0�� ���ö� ���� ���� �÷�
		board[nx][ny][i] = t[t_idx++];
	}

	if (board[nx][ny][4] != 0) return true;	// �������� �ᱹ 4��°���� ���� ����� �״�� ���� ��
	else return false;
}

int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> board[i][j][0];
	
	for (int i = 1; i <= K; i++) {
		cin >> pieces[i].x >> pieces[i].y >> pieces[i].d;
		board[pieces[i].x][pieces[i].y][1] = i;
	}

	int ans = -1;
	bool is_finished = false;
	
	for (int t = 1; t <= 1000; t++) {
		for (int i = 1; i <= K; i++) {
			if (movePiece(i)) {
				is_finished = true;
				ans = t;
				break;
			}
		}
		if (is_finished) break;
	}
	cout << ans;
	return 0;
}