#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int T, N, M, X, Y, ans;
int board[50][50];
int visited[50][50];
int slimeIdx[50][50];
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
bool is_chaged;

bool check_gap(int origin_x, int origin_y, int next_x, int next_y) {
	int gap = abs(board[origin_x][origin_y] - board[next_x][next_y]);
	if (gap >= X && gap <= Y) return true;
	else return false;
}

void dfs(int x, int y, int s_idx) {
	visited[x][y] = true;
	slimeIdx[x][y] = s_idx;
	for (int i = 0; i < 4; i++) {
		int n_x = x + dir[i][0], n_y = y + dir[i][1];
		if (n_x < 0 || n_y < 0 || n_x >= N || n_y >= M || visited[n_x][n_y] || !check_gap(x,y,n_x,n_y)) continue;
		dfs(n_x, n_y, s_idx);
		is_chaged = true;
	}
}

void check() {
	// 초기화
	memset(visited, 0, sizeof(visited)), memset(slimeIdx, 0, sizeof(slimeIdx));
	
	int idx = 0;
	// 1. 각 슬라임마다 DFS를 돌린다
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) 
			if (!visited[i][j]) dfs(i,j, idx++);

	if (!is_chaged) return;
	
	// 2. 그 후, DFS의 결과인 slimeIdx 행렬로 검사를 시작할건데
	for (int i = 0; i < idx; i++) {
		int val = 0, slimeNum = 0;
		
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (slimeIdx[j][k] == i) {
					slimeNum++;
					val += board[j][k];
				}
			}
		}
		
		if (slimeNum == 1) continue;
		else if (slimeNum == 0) cout << "ERROR: " << i ;
		
		val = val / slimeNum;
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (slimeIdx[j][k] == i) {
					board[j][k] = val;
				}
			}
		}
	}
}

int main() {
	cin >> T;
	for (int test = 1; test <= T; test++) {
		// 초기화
		ans = 0;
		// 입력
		cin >> N >> M;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cin >> board[i][j];

		cin >> X >> Y;
		
		while (1) {
			is_chaged = false;
			check();
			if (is_chaged) ans++;
			else break;
		}
		cout << "#" << test << " " << ans << endl;
	}
	return 0;
}