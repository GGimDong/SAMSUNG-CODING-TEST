#include <iostream>

using namespace std;

int point = 0;
int N, t, x, y;
int blue[4][6] = { 0, };
int green[6][4] = { 0, };;

int dir[2][2] = { {0,1}, {1,0} }; // 0: BLUE, 1: GREEN
int t_dir[4][2] = { {0,0}, {0,0} ,{0,1}, {1,0} };

void print_board() {
	cout << "BLUE" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			cout << blue[i][j];
		}cout << endl;
	}
	cout << "GREEN" << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << green[i][j];
		}cout << endl;
	}
}

void move(int origin_x, int origin_y, int d) {
	int next_x = origin_x + dir[d][0] , next_y = origin_y + dir[d][1];
	if (d == 0) {
		if (next_y > 5 || blue[next_x][next_y] != 0) return;
		int idx = blue[origin_x][origin_y];
		blue[origin_x][origin_y] = 0, blue[next_x][next_y] = idx;
	}
	else if (d == 1) {
		if (next_x > 5 || green[next_x][next_y] != 0) return;
		int idx = green[origin_x][origin_y];
		green[origin_x][origin_y] = 0, green[next_x][next_y] = idx;
	}
	move(next_x, next_y, d);
}

void moveBig(int x_1, int y_1, int d, int t) {
	int x_2 = x_1 + t_dir[t][0], y_2 = y_1+ t_dir[t][1];
	int next_x_1 = x_1 + dir[d][0], next_y_1 = y_1 + dir[d][1], next_x_2 = x_2 + dir[d][0], next_y_2 = y_2 + dir[d][1];
	//cout << "DEBUG: 원래 자리: " << x_1 << "," << y_1 << "&" << x_2 << "," << y_2 << " 이동자리" << next_x_1 << "," << next_y_1 << "&" <<  next_x_2 << ","<< next_y_2 << endl;
	if (d == 0) {
		if (next_y_1 > 5 || next_y_2 > 5 || blue[next_x_1][next_y_1] != 0 || blue[next_x_2][next_y_2] != 0) return;
		int idx = blue[x_1][y_1];
		blue[x_1][y_1] = 0, blue[next_x_1][next_y_1] = idx;
		blue[x_2][y_2] = 0, blue[next_x_2][next_y_2] = idx;
	}
	else if (d == 1) {
		if (next_x_1 > 5|| next_x_2 >5 || green[next_x_1][next_y_1] != 0 || green[next_x_2][next_y_2] != 0) return;
		int idx = green[x_1][y_1];
		green[x_1][y_1] = 0, green[next_x_1][next_y_1] = idx;
		green[x_2][y_2] = 0, green[next_x_2][next_y_2] = idx;
	}
	moveBig(next_x_1, next_y_1, d, t);
}

bool erase_line() {
	bool is_change = false;
	for (int j = 2; j < 6; j++) {
		if (green[j][0] != 0 && green[j][1] != 0 && green[j][2] != 0 && green[j][3] != 0) {
			green[j][0] = 0, green[j][1] = 0, green[j][2] = 0, green[j][3] = 0;
			point++;
			is_change = true;
		}

		if (blue[0][j] != 0 && blue[1][j] != 0 && blue[2][j] != 0 && blue[3][j] != 0) {
			blue[0][j] = 0, blue[1][j] = 0, blue[2][j] = 0, blue[3][j] = 0;
			point++;
			is_change = true;
		}
	}
	return is_change;
}

int main() {
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> t >> x >> y;
		
		// 1. 시작점에 놓은 블럭을 발사지역으로 놓음
		blue[x][0]=i; green[0][y] = i;
		if (t == 2) {
			blue[x][1] = i; green[0][y+1] = i;
		}
		else if (t == 3) { 
			blue[x+1][0] = i; green[1][y] = i; 
		}

		// 2. 목표로 하강하는데 사실 2줄을 하강시키면 됨
		if (t == 1) {
			move(x, 0, 0);
			move(0, y, 1);
		}
		else if (t == 2) {
			move(x, 1, 0), move(x, 0, 0);
			moveBig(0, y, 1, t);
		}
		else if (t == 3) {
			moveBig(x, 0, 0, t);
			move(1, y, 1), move(0, y, 1);
		}

		// 3. 줄 제거 하강, 혹시 하강때 제거되면 반복
		while (erase_line()) {
			for (int j = 4; j >= 0; j--)
				for (int k = 0; k < 4; k++)
					if (green[j][k] != 0) {
						if (k != 3 && green[j][k] == green[j][k + 1]) {
							moveBig(j, k, 1, 2);
							k++;
						}
						else {
							move(j, k, 1);
						}
					}
			for (int j = 4; j >= 0; j--)
				for (int k = 0; k < 4; k++)
					if (blue[k][j] != 0) {
						if (k != 3 && blue[k][j] == blue[k + 1][j]) {
							moveBig(k, j, 0, 3);
							k++;
						}
						else {
							move(k, j, 0);
						}
					}
		}

		// 4. 만약 흘러넘치면 푸쉬스
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k < 4; k++) {
				if (blue[k][j] != 0) {
					for (int l = 4; l >= 0; l--) for (int m = 0; m < 4; m++) blue[m][l+1] = blue[m][l];
					blue[0][0] = 0, blue[1][0] = 0, blue[2][0] = 0, blue[3][0] = 0;
					break;
				}
			}
		}
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k < 4; k++) {
				if (green[j][k] != 0) {
					for (int l = 4; l >= 0; l--) for (int m = 0; m < 4; m++) green[l + 1][m] = green[l][m];
					green[0][0] = 0, green[0][1] = 0, green[0][2] = 0, green[0][3] = 0;
					break;
				}
			}
		}
		//print_board();
	}

	int ans = 0;
	for(int i=2;i<6;i++)
		for (int j = 0; j < 4; j++)
		{
			if (blue[j][i] != 0) ans++;
			if (green[i][j] != 0) ans++;
		}

	cout << point << endl;
	cout << ans << endl;
	return 0;
}