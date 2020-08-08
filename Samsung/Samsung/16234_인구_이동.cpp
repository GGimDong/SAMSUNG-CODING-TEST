#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };
int N, L, R;
int arr[50][50], arrIdxp[50][50];
bool visited[50][50];
bool is_changed;
int avg[3000][2];

void check(int x, int y, int idx) {
	visited[x][y] = true;
	arrIdxp[x][y] = idx;

	avg[idx][0] += arr[x][y],avg[idx][1]++;

	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0], ny = y + dir[i][1];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N || visited[nx][ny]) continue;
		int gap = abs(arr[x][y] - arr[nx][ny]);
		if (gap >= L && gap <= R) {
			is_changed = true;
			check(nx, ny, idx);
		}
	}
}

int main() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> arr[i][j];

	int ans = 0;

	while (1) {
		// 초기화
		is_changed = false;
		memset(visited, 0, sizeof(visited)); 
		memset(arrIdxp, 0, sizeof(arrIdxp));
		memset(avg, 0, sizeof(avg));

		int idx = 0;

		// 인구 이동 시키기 전에 먼저 체크
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (!visited[i][j]) check(i, j, ++idx);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				int arrIdx = arrIdxp[i][j];
				arr[i][j] = avg[arrIdx][0] / avg[arrIdx][1];
			}
		
		if (!is_changed) break;
		ans++;
	}

	cout << ans;
	return 0;
}