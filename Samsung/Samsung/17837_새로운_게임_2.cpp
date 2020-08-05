#include <iostream>

using namespace std;

struct Piece {
	int x, y, d;
	void changeDir() {
		if (d == 1) d = 2;
		else if (d == 2) d = 1;
		else if (d == 3) d = 4;
		else if (d == 4) d = 3;
	}
}pieces[11];

int dir[5][2] = { {0,0}, {0, 1}, {0,-1}, {-1,0}, {1,0} };
int map[14][14], order[14][14][10];
int N, K;

/*디버깅*/void printOrder() {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (order[i][j][0] != 0) {
				cout << "(" << i << "," << j << "): ";
				for (int k = 0; k < K; k++) {
					if (order[i][j][k] == 0) break;
					cout << order[i][j][k] << "("<< pieces[order[i][j][k]].d <<") ";
				}
				cout << endl;
			}
}

void moveWhite(int x, int y, int nx, int ny, int level) {
	int s;
	for (int i = 0; i < 10; i++) 
		if (order[nx][ny][i] == 0) {
			s = i;
			break;
		}
	
	for (int i = level; i < 10; i++) {
		int idx = order[x][y][i];
		if (idx == 0) break;
		pieces[idx].x = nx, pieces[idx].y = ny;

		order[nx][ny][s++] = idx;
		order[x][y][i] = 0;

	}
	//printOrder();
}

// 뒤로 돌아서 가세요
void moveBlue(int idx, int level) {
	pieces[idx].changeDir();
	int x = pieces[idx].x, y = pieces[idx].y, d = pieces[idx].d;
	int nx = x + dir[d][0], ny = y + dir[d][1];

	// 뒤돌아도 못가면 바로 끝
	if (nx == 0 || ny == 0 || nx == N + 1 || ny == N + 1) return;
	else if (map[nx][ny] == 2) return;

	moveWhite(x, y, nx, ny, level);
}

void move(int idx) {
	int x = pieces[idx].x, y = pieces[idx].y, d = pieces[idx].d;
	int nx = x + dir[d][0], ny = y + dir[d][1];
	int level;
	for (int i = 0; i < K; i++) if (order[x][y][i] == idx) level = i;

	// 못 가는 곳이거나 파란곳으로 향할 땐 동일하게 처리
	if (nx == 0 || ny == 0 || nx == N + 1 || ny == N + 1) moveBlue(idx, level);
	else if (map[nx][ny] == 2) moveBlue(idx, level);
	else {
		// 움직임 이동
		moveWhite(x, y, nx, ny, level);
		// 빨간색이면 순서 바꾸기만 추가
		if (map[nx][ny] == 1) {
			int temp[10] = { 0, };
			for (int i = 0; i < K; i++) if (order[nx][ny][i] == idx) level = i;
			int t_i = 0;
			for (int i = 9; i >= level; i--) {
				if (order[nx][ny][i] != 0) temp[t_i++] = order[nx][ny][i];
			}

			//cout << "DEBUG ";
			for (int i = 0; i < 10; i++) {
				if (temp[i] == 0) break;
				//cout << temp[i] << " ";
				order[nx][ny][level + i] = temp[i];
			}//cout << endl;
		}
	}
}

int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) 
			cin >> map[i][j];

	for (int i = 1; i <= K; i++) {
		cin >> pieces[i].x >> pieces[i].y >> pieces[i].d;
		order[pieces[i].x][pieces[i].y][0] = i;
	}
	

	for (int time = 1; time <= 1000; time++) {
		//cout << "Time: " << time << endl;
		for (int i = 1; i <= K; i++) {
			//cout << "Idx: " << i << endl;
			move(i);
			printOrder();
			system("pause");
			for (int j = 1; j <= N; j++)
				for (int k = 1; k <= N; k++)
					if (order[j][k][3] != 0) {
						cout << time;
						return 0;
					}
	}
	}
	cout << -1;
	return 0;
}