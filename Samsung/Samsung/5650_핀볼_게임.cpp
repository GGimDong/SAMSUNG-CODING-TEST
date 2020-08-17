#include <iostream>

using namespace std;

int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };	// 0상 1하 2좌 3우 
int T, N;
int arr[102][102];	// 1 ~ 100: idx, 101과 0은 out 처리
int ans;

// 해당 방향의 반대방향을 출력해줌
int oppositeDir(int d) {
	if (d == 0) return 1;
	else if (d == 1) return 0;
	else if (d == 2) return 3;
	else if (d == 3) return 2;
}

// 원래 위치인가 확인
bool is_origin(int a, int b, int c, int d) {
	if (a == c && b == d) return true;
	else return false;
}

// 벽에 박을 녀석 종류와 지금 방향을 넣으면, 바뀔 방향이 나옴
int crashedDir(int arrValue, int currentDir) {
	// ㄴ
	if (arrValue == 1) {
		if (currentDir == 0 || currentDir == 3) return oppositeDir(currentDir);
		else if (currentDir == 1) return 3;
		else if (currentDir == 2) return 0;
	}
	// ㄱ 대칭
	else if (arrValue == 2) {
		if (currentDir == 3 || currentDir == 1) return oppositeDir(currentDir);
		else if (currentDir == 0) return 3;
		else if (currentDir == 2) return 1;
	}
	// ㄱ
	else if (arrValue == 3) {
		if (currentDir == 2 || currentDir == 1)  return oppositeDir(currentDir);
		else if (currentDir == 0) return 2;
		else if (currentDir == 3) return 1;
	}
	// ㄴ 대칭
	else if (arrValue == 4) {
		if (currentDir == 0 || currentDir == 2) return oppositeDir(currentDir);
		else if (currentDir == 1) return 2;
		else if (currentDir == 3) return 0;
	}
	// ㅁ
	else if (arrValue == 5) return oppositeDir(currentDir);

	// 벽에 박는 것들이 아닐 경우, 그냥 일반 방향을 출력
	return currentDir;
}

void simulate(int start_x, int start_y, int d) {
	int point = 0;
	int x = start_x, y = start_y;

	while (1) {
		/*디버깅*/ //cout << x << "," << y << ": " << d << endl; system("pause");
		
		int value = arr[x][y];

		// 목표지점에 도달
		if (value == -1) {
			/*디버깅*/ //cout << "Mission complete: " << point << endl;
			break;
		}
		// 웜홀인 경우엔 워프해드림
		else if (value >= 6) {
			bool flag = false;
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (i == x && j == y) continue;
					if (arr[i][j] == value) {
						x = i, y = j;
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
		}

		// 현재 지점에서 방향이 바뀌는가?
		int nextDir = crashedDir(value, d);

		// 방향이 변한 상황, 박은 것임
		if (nextDir != d) {
			/*디버깅*/ //cout << "Crashed! " << d  <<" to " << nextDir << endl;
			point++;
			d = nextDir;
		}

		// 해당 방향으로 한 칸 전진!
		x += dir[d][0], y += dir[d][1];

		//원래 자리로 돌아온 경우
		if (is_origin(x, y, start_x, start_y)) {
			/*디버깅*/ //cout << "Origin position: " << point <<endl;
			break;
		}
	}
	if (point > ans) ans = point;
}

void printBoard() {
	for (int i = 0; i <= N + 1; i++){
		for (int j = 0; j <= N + 1; j++) {
			cout << arr[i][j] << " ";
		}cout << endl;
	}cout << endl;
}

int main() {
	cin >> T; /*나중에 T로 묶어*/

	for (int test = 1; test <= T; test++) {
		ans = 0;
		cin >> N;
		for (int i = 0; i <= N + 1; i++)
			for (int j = 0; j <= N + 1; j++) {
				if (i == 0 || j == 0 || i == N + 1 || j == N + 1) arr[i][j] = 5;
				else cin >> arr[i][j];
			}

		//printBoard();

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (arr[i][j] == 0) {
					for (int k = 0; k < 4; k++) simulate(i, j, k);
				}
			}
		}

		cout << "#" << test << " " << ans << endl;
	}
	return 0;
}