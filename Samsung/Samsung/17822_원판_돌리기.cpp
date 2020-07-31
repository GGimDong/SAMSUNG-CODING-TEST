#include <iostream>

using namespace std;

int N, M, T, x, d, k;
float arr[55][55];
int dx[4] = { 1,0,0,-1 };
int dy[4] = { 0,1,-1,0 };
bool is_changed;

void rotate(int x) {
	float temp = arr[x][M-1];
	for (int i = M-1; i > 0 ; i--) arr[x][i]= arr[x][i-1];
	arr[x][0] = temp;
}

void dfs(int x, int y, float value) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		
		if (ny == -1) ny = M - 1;
		if (ny == M) ny = 0;

		if (nx < 0 || nx >= N || arr[nx][ny] != value) continue;
		if (arr[x][y] != -1) {
			is_changed = true;
			arr[x][y] = -1;
		}
		arr[nx][ny] = -1;
		dfs(nx, ny, value);
	}
}
/*
void print_board() {
	for (int i = 0; i < N; i++){		
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == -1) cout << "X ";
			else cout << arr[i][j]<<" ";
		}cout << endl;
	}cout << endl;
}
*/
int main() {
	cin >> N >> M >> T;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> arr[i][j];

	for (int i = 0; i < T; i++) {
		cin >> x >> d >> k;
		// 1. rotate
		if (d == 1) k = M - k;
		for(int j = 1;  (x *j) <=N ; j++){
			//cout << "DEBUG: "<< x*j << endl;
			for (int kk = 0; kk < k; kk++) rotate(x *j - 1);
		}
		is_changed = false;
		
		//print_board();
		// 2. 같은 녀석들 제거, DFS로 해도될 것 같음
		for (int x = 0; x < N; x++) 
			for (int y = 0; y < M; y++)
				if (arr[x][y] != -1) dfs(x, y, arr[x][y]);

		if (!is_changed) {
			float avg = 0, num = 0;
			for (int x = 0; x < N; x++)
				for (int y = 0; y < M; y++)
					if (arr[x][y] != -1) {
						num++;
						avg += arr[x][y];
					}
			
			if (num > 1) {
				avg = avg / num;
				for (int x = 0; x < N; x++)
					for (int y = 0; y < M; y++) {
						if (arr[x][y] == -1) continue;
						else if (arr[x][y] < avg) arr[x][y]++;
						else if (arr[x][y] > avg) arr[x][y]--;
						else if (arr[x][y] == avg) {}
					}
			}

		}
	}

	float ans = 0;
	for (int x = 0; x < N; x++)
		for (int y = 0; y < M; y++)
			if (arr[x][y] != -1) ans += arr[x][y];
	cout << (int)ans;
	
	return 0;
}