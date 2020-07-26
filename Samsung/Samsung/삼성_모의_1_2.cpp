#include <iostream>

using namespace std;

const int MAX = 10;
const int F_MAX = 5;

struct map {
	int x, y, kind;
};

// 0 위 1 오 2 아 3 왼
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };

int result, M, N;

int board[MAX][MAX];
int temp_board[MAX][MAX];

int round[F_MAX]; // 수도꼭지의 몇 번 90도 돌아간 정보
map v[F_MAX];
int len = 0;

void water(int x, int y, int dir) {
	while (1) {
		int next_x = x + dx[dir], next_y = y + dy[dir];
		if (next_x < 0 || next_y < 0 || next_x >= M || next_y >= N || temp_board[next_x][next_y] == 6) return;
		temp_board[next_x][next_y] = 9;
		x = next_x, y = next_y;
	}
}

void calc() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			temp_board[i][j] = board[i][j];
		}
	}

	// 물줄기 뿜뿜!

	for (int i = 0; i < len; i++) {
		map point = v[i];
		if (point.kind == 1) {
			water(point.x, point.y, round[i]);
		}
		else if (point.kind == 5) {
			for (int j = 0; j < 4; j++) {
				water(point.x, point.y, j);
			}
		}
		else if (point.kind == 2) {
			int next = round[i] + 2;
			if (next > 3) next -= 4;
			water(point.x, point.y, round[i]);
			water(point.x, point.y, next);
		}
		else if (point.kind == 3) {
			int next = round[i] + 1;
			if (next == 4) next = 0;
			water(point.x, point.y, round[i]);
			water(point.x, point.y, next);
		}
		else { // 4
			int not_idx = round[i] + 2;
			if (not_idx > 3) not_idx = not_idx - 4;
			for (int j = 0; j < 4; j++) {
				if (j != not_idx) water(point.x, point.y, j);
			}
		}
	}


	int ans = 0;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (temp_board[i][j] == 0) {
				ans++;
			}
		}
	}

	if (result == -1 || result > ans) result = ans;
}


void doRecursion(int current) {
	if (current >= len) {
		calc();
	}
	else {
		for (int i = 0; i < 4; i++) {
			round[current] = i;
			doRecursion(current + 1);
		}
	}
}

map make_point(int a, int b, int c) {
	map temp;
	temp.x = a, temp.y = b, temp.kind = c;
	return temp;
}

int main() {
	int T;
	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++) {
		result = -1;
		cin >> M >> N;
		len = 0;

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
				if (board[i][j] != 0 && board[i][j] != 6) {
					v[len++] = make_point(i, j, board[i][j]);
				}
			}
		}

		doRecursion(0);

		cout << "#" << test_case << " " << result << endl;
	}
	return 0;
}