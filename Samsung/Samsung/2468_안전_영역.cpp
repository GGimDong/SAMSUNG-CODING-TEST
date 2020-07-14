/*
	"아무 지역도 물에 잠기지 않을 수도 있다."
	즉, 초기값이 1이라는 소리...
*/
#include <iostream>

using namespace std;

const int MAX = 101;

int N;
int board[MAX][MAX];
int sinked_board[MAX][MAX];

int ans = 1;
int temp_ans;
int dir[4][2] = {
	{1,0},
	{-1,0},
	{0,1},
	{0,-1}
};

void print_board() {

	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << sinked_board[i][j];
		cout << endl;
	}
}

void dfs(int x, int y, int idx) {
	sinked_board[x][y] = idx;
	for (int i = 0; i < 4; i++) {
		int dx = dir[i][0], dy = dir[i][1];
		int next_x = x + dx, next_y = dy + y;
		if (next_x >= 0 && next_y >= 0 && next_x < N && next_y < N && sinked_board[next_x][next_y] == -1)
			dfs(x + dx, y + dy, idx);
	}
}

int check_island() {
	int idx = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sinked_board[i][j] == -1)
				dfs(i, j,++idx);
	return idx;
}


bool sink_down(int h) {
	bool no_land = false;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (board[i][j] <= h)
				sinked_board[i][j] = 0;
			else {
				sinked_board[i][j] = -1;
				no_land = true;
			}

	return no_land;
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> board[i][j];

	for (int i = 1; i <= 100; i++) {
		if (!sink_down(i)) 
			break;
		
		temp_ans = check_island();
		
		if (temp_ans > ans)
			ans = temp_ans;
	}
	
	cout << ans;

	return 0;
}