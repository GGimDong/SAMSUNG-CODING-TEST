#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 21;

struct map {
	int x, y;
	bool done = false;
}taxi, guestlist[401], dstlist[401];

int N, M, G;
int board[MAX][MAX];

int taxi_board[MAX][MAX];
int temp_board[MAX][MAX];

int guest_dst[401];

int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };

map make_map(int a, int b) {
	map t;
	t.x = a, t.y = b;
	return t;
}

// src -> dst 의 거리, 도착이 안되면 -1
int drive(map src, map dst) {
	// 작업할 temp board 초기화
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			temp_board[i][j] = board[i][j];

	queue<map> q;
	temp_board[src.x][src.y] = 1;
	q.push(src);

	while (!q.empty()) {
		map point = q.front();
		q.pop();
		int time = temp_board[point.x][point.y];

		if (point.x == dst.x && point.y == dst.y) {
			return time - 1;
		}

		for (int i = 0; i < 4; i++) {
			int n_x = point.x + dir[i][0], n_y = point.y + dir[i][1];
			if (n_x <= 0 || n_y <= 0 || n_x > N || n_y > N || temp_board[n_x][n_y] != 0) continue;
			temp_board[n_x][n_y] = time + 1;
			q.push(make_map(n_x, n_y));
		}
	}

	return -1;
}

// 택시에서 가장 가까운 손님을 태우고 데려다 놓음
void simulate() {
	// 1. 택시에서 손님까지의 거리를 구함, 못 가거나 이미 구한 녀석은 -1
	for (int i = 1; i <= M; i++) {
		if (guestlist[i].done) { guest_dst[i] = -1; }
		else guest_dst[i] = drive(taxi, guestlist[i]);
	}



	/*DEBUG*/
	//cout << "TAXI(" << taxi.x << "," << taxi.y << "): ";
	//for (int i = 1; i <= M; i++) cout << guest_dst[i] << " "; cout << endl;



	// 2. 가장 가까운 녀석을 찾음, 근데 가까운게 여러 개면 지도 중심으로 봐야함
	int minIdx = -1;
	int minValue = 9999999;
	for (int i = 1; i <= M; i++) {
		if (guest_dst[i] != -1) {
			if (minIdx == -1) {
				minIdx = i, minValue = guest_dst[i];
			}
			else if (minValue > guest_dst[i]) {
				minIdx = i, minValue = guest_dst[i];
			}
			else if (minValue == guest_dst[i]) {
				if (guestlist[i].x < guestlist[minIdx].x) minIdx = i;
				else if (guestlist[i].x == guestlist[minIdx].x && guestlist[i].y < guestlist[minIdx].y) minIdx = i;
			}
		}
	}

	/*DEBUG*/
	//cout << "Shortest idx: " << minIdx << ", (To Guest) 필요 가스: "<< minValue << "현재 남은 GAS: " << G << endl;

	if (minIdx == -1 || minValue > G) {
		G = -1;
		return;
	}
	G -= minValue;

	// 3. 그곳으로 이동했다 하고, 목적지로 돌아가주자!
	int g_dst = drive(guestlist[minIdx], dstlist[minIdx]);

	/*DEBUG*/
	//cout << "(To DST) 필요 가스: " << g_dst <<" "<< " 현재 남은 GAS: " << G << endl;


	if (g_dst == -1 || g_dst > G) {
		G = -1;
		return;
	}
	G -= g_dst;


	guestlist[minIdx].done = true;
	G = G + 2 * g_dst;

	/*DEBUG*/
	//cout << "충전 후 GAS: " << G << endl;

	taxi = dstlist[minIdx];
}


int main() {
	cin >> N >> M >> G;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> board[i][j];

	cin >> taxi.x >> taxi.y;
	for (int i = 1; i <= M; i++) cin >> guestlist[i].x >> guestlist[i].y >> dstlist[i].x >> dstlist[i].y;

	// M명의 사람을 태워야하므로 M번 돌림 
	for (int i = 0; i < M; i++) {
		simulate();
		if (G < 0) {
			cout << "-1";
			return 0;
		}
	}

	cout << G;
	return 0;
}