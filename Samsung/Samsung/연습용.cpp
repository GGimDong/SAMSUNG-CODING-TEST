#include <cstdio>

struct SHARK {
	int x, y, d, prio[4][4];
};

int main() {
	int N, M, K, map[20][20], time[20][20], smell[20][20];
	SHARK shark[401];
	int dx[4] = { -1,1,0,0 };
	int dy[4] = { 0,0,-1,1 };

	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j]) {
				shark[map[i][j]].x = i;
				shark[map[i][j]].y = j;
				smell[i][j] = map[i][j];
				time[i][j] = K;
			}
		}
	}

	for (int i = 1; i <= M; i++)
		scanf("%d", &shark[i].d), shark[i].d--;

	for (int i = 1; i <= M; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				scanf("%d", &shark[i].prio[j][k]), shark[i].prio[j][k]--;

	int now = 0, sharknum = M;
	while (now < 1000) {
		now++;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				map[i][j] = 0;

		for (int i = 1; i <= M; i++) {
			if (shark[i].x == -1) continue;
			bool flag = false;
			for (int j = 0; j < 4; j++) {
				int nd = shark[i].prio[shark[i].d][j];
				int nx = shark[i].x + dx[nd];
				int ny = shark[i].y + dy[nd];
				if (nx < 0 || ny < 0 || nx == N || ny == N || time[nx][ny] >= now) continue;
				flag = true;
				if (map[nx][ny]) {
					shark[i].x = -1;
					sharknum--;
					break;
				}
				shark[i].x = nx;
				shark[i].y = ny;
				shark[i].d = nd;
				map[nx][ny] = i;
				smell[nx][ny] = i;
				break;
			}
			if (flag) continue;
			for (int j = 0; j < 4; j++) {
				int nd = shark[i].prio[shark[i].d][j];
				int nx = shark[i].x + dx[nd];
				int ny = shark[i].y + dy[nd];
				if (nx < 0 || ny < 0 || nx == N || ny == N || smell[nx][ny] != i) continue;
				shark[i].x = nx;
				shark[i].y = ny;
				shark[i].d = nd;
				break;
			}
		}
		for (int i = 1; i <= M; i++) {
			if (shark[i].x == -1) continue;
			time[shark[i].x][shark[i].y] = now + K;
		}

		if (sharknum == 1) {
			printf("%d", now);
			return 0;
		}
	}

	printf("-1");
	return 0;
}