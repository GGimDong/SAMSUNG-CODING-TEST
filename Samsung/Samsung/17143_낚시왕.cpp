/*
	memset은 빠르구나... 의심하지 말자
	다만, 시간 초과가 나면, 시간초과를 일부러 내는 장치가 있음을 유의하자.
*/
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct shark {
	int x, y, speed, d, size;
	bool is_dead = false;

	void changeDir() {
		if (d == 1) d = 2;
		else if (d == 2) d = 1;
		else if (d == 3) d = 4;
		else if (d == 4) d = 3;
	}

	void die() { is_dead = true; }
};

shark make_shark(int a, int b, int c, int d, int e) {
	shark temp;
	temp.x = a, temp.y = b, temp.speed = c, temp.d = d, temp.size = e;
	return temp;
}

int dir[5][2] = { {0,0}, {-1,0}, {1,0}, {0,1}, {0,-1} };
int arr[101][101];
int temp[101];
int R, C, M, a, b, c, d, e;
vector<shark> v;	// 인덱스가 0부터 시작이라 idx -1 번째 상어를 찾으면 됨.

/*디버깅*/ //void printBoard() { cout << endl; for (int i = 1; i <= R; i++) { for (int j = 1; j <= C; j++) { cout << arr[i][j] << " "; }cout << endl; } }

void sharkMove() {
	memset(arr, 0, sizeof(arr));
	for (int sharkIdx = 0; sharkIdx < M; sharkIdx++) {	// 0 ~ M-1
		if (v[sharkIdx].is_dead) continue;	// 죽은 애는 패스
		int x = v[sharkIdx].x, y = v[sharkIdx].y, speed = v[sharkIdx].speed, d = v[sharkIdx].d;
		
		// TODO: 시간 줄이기용으로 speed 줄여보기 1000은 너무큰데
		if (d == 1 || d == 2) {// 위 아래면, 
			int max = 2 * (R - 1);
			if (speed > max) speed = speed % max;
		}
		else {
			int max = 2 * (C - 1);
			if (speed > max) speed = speed % max;
		}


		for (int i = 0; i < speed; i++) {	// d방향으로 speed만큼 움직임
			int nx = x + dir[d][0], ny = y+dir[d][1];
			if (nx < 1 || ny < 1 || nx > R || ny > C) {	// 벽에 박은 상태면
				v[sharkIdx].changeDir(); //	뒤로 돌아서
				d = v[sharkIdx].d, nx = x + dir[d][0], ny = y+dir[d][1];	// 해당 방향을 다시 잡아줌
			}
			x = nx, y = ny;
		}
		v[sharkIdx].x = x, v[sharkIdx].y = y;
		//cout << sharkIdx << "살아있고 " << x << y << endl;
		if(arr[x][y] == 0) arr[x][y] = sharkIdx + 1;
		else {
			int size_1 = v[arr[x][y] - 1].size , size_2 = v[sharkIdx].size;
			
			if (size_1 > size_2) v[sharkIdx].die();	// 원래 있던 놈이 더 크면 걍 뒤짐
			else {	// 새로 들어온놈이 더크면
				v[arr[x][y] - 1].die();
				arr[x][y] = sharkIdx + 1;
			}
		}
	}
}

int main() {
	int ans = 0;
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		cin >> a >> b >> c >> d >> e;
		v.push_back(make_shark(a, b, c, d, e));
	}
	
	for (int i = 1; i <= C; i++) {
		for (int j = 0; j < M; j++) if (!v[j].is_dead) arr[v[j].x][v[j].y] = j + 1;
		// i 번째의 상어를 잡자!
		for (int j = 1; j <= R; j++) {
			if (arr[j][i] != 0) {
				int idx = arr[j][i] -1;
				ans += v[idx].size, v[idx].die();
				arr[j][i] = 0;
				break;
			}
		}

		sharkMove();
		//printBoard(), system("pause");
	}

	cout << ans;
	return 0;
}