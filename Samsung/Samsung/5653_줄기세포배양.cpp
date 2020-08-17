#include <iostream>
#include <cstring>

using namespace std;

struct point {
	int life, time;
	bool is_cell, is_on, is_dead;

	void init(int input) {
		life = input, time = 0 , is_cell = true, is_on = false, is_dead = false;
	}

	void reset() {
		life = 0, time = 0, is_cell = false, is_on = false;
	}

}map[350][350];

int T, N, M, K, temp, ans;
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
int tempArr[350][350];

int main() {

	cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		memset(map, 0, sizeof(map));
		cin >> N >> M >> K;
		int s = K / 2;
		ans = 0;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				cin >> temp;
				if (temp != 0) map[s + i][s + j].init(temp);
				else  map[s + i][s + j].reset();
			}

		for (int time = 0; time < K; time++) {
			memset(tempArr, 0, sizeof(tempArr));
			// 맵에 cell을 찾자
			for (int x = 0; x < K + N; x++)
				for (int y = 0; y < K + M; y++) {
					// cell이 아니거나 죽었으면 그대로 패스
					if (!map[x][y].is_cell || map[x][y].is_dead) continue;

					// 활성화된 녀석은 번식후보지에 넣기
					if (map[x][y].is_on) {
						for (int i = 0; i < 4; i++) {
							int nx = x + dir[i][0], ny = y + dir[i][1];
							if (!map[nx][ny].is_cell && tempArr[nx][ny] < map[x][y].life) {
								tempArr[nx][ny] = map[x][y].life;
							}
						}
					}

					// 시간 1증가시키고 life만큼 지나면 활성화, 2배 지나면 뒤짐
					map[x][y].time++;
					if (!map[x][y].is_on && map[x][y].time >= map[x][y].life) {
						map[x][y].is_on = true;
					}
					else if (map[x][y].is_on && map[x][y].time >= 2 * map[x][y].life) {
						map[x][y].is_dead = true;
					}
				}

			// 후보군들 넣기
			for (int x = 0; x < K + N; x++)
				for (int y = 0; y < K + M; y++)
					if (tempArr[x][y] != 0) map[x][y].init(tempArr[x][y]);

		}

		// 점수 계산
		for (int i = 0; i < K + N; i++)
			for (int j = 0; j < K + M; j++)
				if (!map[i][j].is_dead && map[i][j].is_cell) ans++;

		cout << "#" << tt << " " << ans << endl;
	}

	return 0;
}