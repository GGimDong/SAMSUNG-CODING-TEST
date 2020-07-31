#include <iostream>
#include <cstring>
using namespace std;

int N;
int arr[20][20];
int t_arr[20][20];
bool visited[20][20];

int order[5];
int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // 0상 1하 2좌 3우
int ans = 0;

void gravity(int x, int y, int d) {
	int nx = x + dir[d][0], ny = y + dir[d][1];
	int value = arr[x][y];
	if (nx < 0 || ny < 0 || nx >= N || ny >= N) return;
	if (arr[nx][ny] != 0 && arr[nx][ny] == value && !visited[nx][ny]) {
		arr[x][y] = 0;
		arr[nx][ny] = value * 2;
		visited[nx][ny] = true;
		return;
	}
	else if (arr[nx][ny] == 0) {
		arr[x][y] = 0;
		arr[nx][ny] = value;
		gravity(nx, ny, d);
	}
}

void move(int d) { // d 방향으로 전부 이동시키기
	memset(visited, 0, sizeof(visited));
	if (d == 0 || d == 2) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				gravity(i, j, d);
	}
	else {
		for (int i = N - 1; i >= 0; i--)
			for (int j = N - 1; j >= 0; j--)
				gravity(i, j, d);
	}
}

void calc() {
	// 초기화
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			arr[i][j] = t_arr[i][j];

	for (int i = 0; i < 5; i++) move(order[i]);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (arr[i][j] > ans) ans = arr[i][j];
}

void doRecursion(int current) {
	if (current >= 5) {
		calc();
	}
	else {
		for (int i = 0; i < 4; i++) {
			order[current] = i;
			doRecursion(current + 1);
		}
	}
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> t_arr[i][j];

	doRecursion(0);
	cout << ans;
	return 0;
}