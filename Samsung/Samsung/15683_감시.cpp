#include <iostream>
#include <cstring>

using namespace std;

struct CAM {
	int x, y, kind;
	int dirIdx[4];

	void setDirIdx() { // Init
		memset(dirIdx, 0, sizeof(dirIdx));
		if (kind == 1) dirIdx[0] = 1;
		else if (kind == 2) {
			dirIdx[0] = 1, dirIdx[2] = 1;
		}
		else if (kind == 3) {
			dirIdx[0] = 1, dirIdx[1] = 1;
		}
		else if (kind == 4) {
			dirIdx[0] = 1, dirIdx[1] = 1, dirIdx[2] = 1;
		}
		else if (kind == 5) {
			dirIdx[0] = 1, dirIdx[1] = 1, dirIdx[2] = 1, dirIdx[3] = 1;
		}
	}

	void round() {
		int temp = dirIdx[0];
		for (int i = 0; i < 3; i++) dirIdx[i] = dirIdx[i + 1];
		dirIdx[3] = temp;
	}

}cam[8];

int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };	// 0¿ß 1øÏ 2«œ 3¡¬
int t_board[10][10], board[10][10];	// 0¿∫ ∫Û ƒ≠, 6¿∫ ∫Æ, 1~5¥¬ CCTV
int N, M;
int cam_num = 0;
int order[8];
int ans = 15*15;

void camLight(int x, int y, int d) {
	board[x][y] = 9;
	int nx = x + dir[d][0], ny = y + dir[d][1];
	if (nx < 0 || ny < 0 || nx >= N || ny >= M || board[nx][ny] == 6) return;
	camLight(nx,ny,d);
}

void simulate() {
	// √ ±‚»≠
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			board[i][j] = t_board[i][j];

	for (int i = 0; i < cam_num; i++) {
		cam[i].setDirIdx();
		for (int j = 0; j < order[i]; j++) cam[i].round();
		for (int j = 0; j < 4; j++) if (cam[i].dirIdx[j] == 1) camLight(cam[i].x, cam[i].y, j);
	}
	int result = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] == 0) result++;

	if (result < ans) ans = result;
}

void doRecursion(int current) {
	if (current >= cam_num) simulate();
	else 
		for (int i = 0; i < 4; i++) {
			order[current] = i;
			doRecursion(current + 1);
		}
}

int main() {
	// ¿‘∑¬
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> t_board[i][j];
			if (t_board[i][j] >= 1 && t_board[i][j] <= 5) {
				cam[cam_num].x = i, cam[cam_num].y = j, cam[cam_num++].kind = t_board[i][j];
			}
		}
	}
	doRecursion(0);
	cout << ans;
	return 0;
}