#include <iostream>

using namespace std;
						// 1우	  2좌	  3상	  4하
int dir[5][2] = { {0, 0}, {0,1}, {0,-1}, {-1,0}, {1,0} };
int map[12][12][11];	// 0에는 색깔 1~10은 체스말 존재의 순서
int pieceDir[11];		// 1~10까지 체스말 방향
int pieceInfo[11][2];
int N, K, a, b, c;

void move(int idx) {
	int x = pieceInfo[idx][0], y = pieceInfo[idx][1];
	int color = map[x][y][0], level;

	for (int k = 1; k <= 10; k++) if (map[x][y][k] == idx) level = k;

	/*DEBUG*/cout << idx << "(" << x << "," << y << ") " << level << endl;
	int nx = x + dir[pieceDir[idx]][0], ny = y + dir[pieceDir[idx]][1];

	if (nx < 0 || ny < 0 || nx >= N || ny >= ny || color == 2) { // 바깥쪽, 파란색
		int d = pieceDir[idx];
		if (d == 1) pieceDir[idx] = 2;
		else if (d == 2)pieceDir[idx] = 1;
		else if (d == 3)pieceDir[idx] = 4;
		else if (d == 4)pieceDir[idx] = 3;
		nx = x + dir[pieceDir[idx]][0], ny = y + dir[pieceDir[idx]][1];
		if (map[nx][ny][0] == 2) return;	// 뒤돌아서서 봤드만 못가는 길이면 야는 그냥 고정
	}
	
	// 움직임!
	int s;
	for (int i = 1; i <= 10; i++) 
		if (map[x][y][i] == idx) {
			s = i;
			break;
		}

	for (int i = 1; i <= 10; i++) {
		if (map[nx][ny][i] != 0) continue; 
		map[nx][ny][i] = map[x][y][s];
		map[x][y][s++] = 0;
	}


	if (color == 1){ // 빨간색일 경우, 위아래 반전

	}
		
}

void print_board() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 1; k < 11; k++)
				if (map[i][j][k] != 0)
					cout <<"("<< i << "," << j << ")_"<< k <<": "<< map[i][j][k] << endl;
	cout << endl;
}

int main() {
	cin >> N >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j][0];

	for (int i = 1; i <= K; i++) {
		cin >> a >> b >> pieceDir[i];
		a--, b--, map[a][b][1] = i;
		pieceInfo[i][0] = a, pieceInfo[i][1] = b;
	}

	cout << "Start" << endl; print_board();
	for (int time = 1; time <= 1000; time++) {
		for (int i = 1; i <= K; i++) move(i);
		
		// 4개가 쌓일 경우 종료
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++) 
				if (map[i][j][4] != 0) {
					cout << time;
					return 0;
				}

		cout << "Time: " << time << endl; print_board();
		system("pause");
	}

	cout << -1;
	return 0;
}