#include <iostream>

using namespace std;

int dir[4][2] = { {0,1}, {1,0},{0,-1}, {-1,0} };
int W, H, N;
int arr[15][12], t_arr[15][12];
int order[4];
int ans;

void bomb(int x, int y) {
	int value = arr[x][y];
	arr[x][y] = 0;
	for (int i = 0; i < value; i++) {
		for (int j = 0; j < 4; j++) {
			int nx = x + i*dir[j][0], ny = y + i*dir[j][1];
			if (nx < 0 || ny < 0 || nx >= H || ny >= W || arr[nx][ny] == 0) continue;
			bomb(nx,ny);
		}
	}
}

void gravity(int x, int y) {
	int t = arr[x][y];
	int nx = x + 1;
	if (nx >= H || arr[nx][y] != 0) return;
	arr[x][y] = 0;
	arr[nx][y] = t;
	gravity(nx,y);
}

void shoot(int idx) {
	for (int i = 0; i < H; i++)
		if (arr[i][idx] != 0) {
			bomb(i, idx);
			break;
		}

	for (int i = H-1; i >= 0; i--)
		for (int j = 0; j < W; j++)
			if (arr[i][j] != 0) gravity(i,j);
}

void simulate() {
	// ÃÊ±âÈ­
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			arr[i][j] = t_arr[i][j];

	for (int i = 0; i < N; i++) shoot(order[i]);
	
	int t_ans = 0;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (arr[i][j] != 0) t_ans++;

	if (ans > t_ans) ans = t_ans;
}

void doRecursion(int current) {
	if (current >= N) simulate();
	else {
		for (int i = 0; i < W; i++) {
			order[current] = i;
			doRecursion(current + 1);
		}
	}
}

int main(){
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		ans = 15*12;
		cin >> N >> W >> H;
		
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				cin >> t_arr[i][j];

		doRecursion(0);
		cout << "#" << test << " " << ans << endl;
	}
	return 0;
}