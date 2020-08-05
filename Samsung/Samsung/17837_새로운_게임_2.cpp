#include <iostream>

using namespace std;

int N, K;
int board[15][15][5]; // 0 은 color, 1~4는 order, 4개가 쌓이는 순간 사실상 게임이 끝나므로 그 이상 놓을 필요도 없음!
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

	/*디버깅*/ //system("pause");
	/*디버깅*/ //cout << idx << " (" << x << "," << y << ")" << " → ";

	if (!checkInside(nx, ny) || color == 2) {	// 파란색이거나 못 가는 곳이면 뒤로 돌아야함.
		/*디버깅*/ //cout << " back ";
		pieces[idx].changeDir(), d = pieces[idx].d;
		nx = x + dir[d][0], ny = y + dir[d][1], color = board[nx][ny][0];	// 뒤로 돌았으니, 방향으로 인해 정보를 다시 업데이트
	}

	/*디버깅*/ //cout << " (" << nx << "," << ny << "), Dir:" << d;

	if (!checkInside(nx, ny) || color == 2) {
		/*디버깅*/ //cout << " can't move!" << endl;;
		return false;	// 뒤로 돌아도 못 가면 그냥 끝
	}
	int level; // order에 몇번째인지를 구해야 함.
	for (int i = 1; i <= 4; i++) if (board[x][y][i] == idx) level = i;

	/*디버깅*/ //cout << "원래 위치:" << level << endl;

	int t_idx = 0;
	int t[4] = { 0,0,0,0 };	// 옮길 임시 배열
	for (int i = level; i <= 4; i++) {
		int p_idx = board[x][y][i];
		t[t_idx++] = p_idx;
		board[x][y][i] = 0;
		pieces[p_idx].x = nx, pieces[p_idx].y = ny;
	}

	if (color == 1) { // 빨갱이면 이 t를 뒤바꿔주기
		/*디버깅*/ //cout << " Order change " << endl;
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

	/*디버깅*/ //for (int i = 0; i < 4; i++) cout << t[i] << " "; cout << endl;

	// (x,y) -> (nx, ny) 로 이동
	t_idx = 0;
	for (int i = 1; i <= 4; i++) {
		if (board[nx][ny][i] != 0) continue;	// 0이 나올때 까지 위로 올려
		board[nx][ny][i] = t[t_idx++];
	}

	if (board[nx][ny][4] != 0) return true;	// 마지막에 결국 4번째에도 말이 생기면 그대로 게임 끝
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