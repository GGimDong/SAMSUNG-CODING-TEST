#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAX 50

using namespace std;

int R, C, T;
int board[MAX][MAX];
int d_dust[MAX][MAX];
int ans = 0;
int air_pos[2][2]; // 공기청정기의 위치
/*지워*/ void print_board(){for (int i = 0; i < R; i++) { for (int j = 0; j < C; j++) printf("%d\t",board[i][j]); cout << endl;}}

void cal_dust() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (board[i][j] > 0) ans += board[i][j];
	cout<< ans;
}

void clear_dust_board() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			d_dust[i][j] = 0;
	return;
}

void apply_dust() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			board[i][j] = d_dust[i][j];
	board[air_pos[0][0]][air_pos[0][1]] = -1;
	board[air_pos[1][0]][air_pos[1][1]] = -1;
	clear_dust_board();
}

/*
	(r, c)에 있는 미세먼지는 인접한 네 방향으로 확산된다.
	인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
	확산되는 양은 Ar,c/5이고 소수점은 버린다.
	(r, c)에 남은 미세먼지의 양은 Ar,c - (Ar,c/5)×(확산된 방향의 개수) 이다.
*/

void spread(int x, int y) {
	int spread_num = 0; // 옆이 벽이거나 공기청정기면 퍼지지 못함.
	int total_dust = board[x][y];
	int spread_dust = board[x][y] / 5;

	// 좌우 상하 확인
	if (y > 0 && board[x][y - 1] != -1) {
		d_dust[x][y - 1] += spread_dust;
		spread_num++;
	}
	if (y < C - 1 && board[x][y + 1] != -1) { 
		d_dust[x][y + 1] += spread_dust;
		spread_num++; 
	}
	if (x > 0 && board[x - 1][y] != -1) {
		d_dust[x - 1][y] += spread_dust;
		spread_num++;
	}
	if (x < R - 1 && board[x + 1][y] != -1) {
		d_dust[x + 1][y] += spread_dust;
		spread_num++;
	}

	d_dust[x][y] += total_dust - spread_dust * spread_num;
	return;
}

void spread_dust() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (board[i][j] > 0)
				spread(i, j);
	apply_dust();
}

void generate_aircleaner() {
	// 위쪽 먼저
	int i = air_pos[0][0];
	int j = air_pos[0][1];
	while ( i > 0) {
		if(board[i][j] != -1)
			board[i][j] = board[i-1][j];
		i--;
	}
	j = 0;
	while (j < C-1) {
		board[0][j] = board[0][j + 1];
		j++;
	}

	i = 0;
	j = C-1;
	while (i < air_pos[0][0]) {
		board[i][j] = board[i+1][j];
		i++;
	}
	i = air_pos[0][0];
	j = C - 1;
	while (j > 0) {
		if (board[i][j-1] != -1)
			board[i][j] = board[i][j - 1];
		else
			board[i][j] = 0;
		j--;
	}

	// 아래쪽
	i = air_pos[1][0]+1;
	j = air_pos[1][1];
	while (i < R-1) {
		board[i][j] = board[i + 1][j];
		i++;
	}
	i = R - 1;
	j = 0;
	while (j < C-1) {
		board[i][j] = board[i][j+1];
		j++;
	}
	i = R - 1;
	j = C - 1;
	while (i > air_pos[1][0]) {
		board[i][j] = board[i-1][j];
		i--;
	}
	i = air_pos[1][0];
	j = C - 1;
	while (j>0) {
		if (board[i][j-1] == -1)
			board[i][j] = 0;
		else
			board[i][j] = board[i][j - 1];
		j--;
	}

}

int main() {
	ifstream input;
	input.open("input/input.txt");

	input >> R >> C >> T;
	int temp;
	int t = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			input >> temp;  
			board[i][j] = temp;
			if (temp == -1) {
				air_pos[t][0] =i;
				air_pos[t][1] = j;
				t++;
			}
		}

	for (int i = 0; i < T; i++) {
		spread_dust();
		generate_aircleaner();
		/*지워*///print_board();
	}
	
	cal_dust();
	return 0;
}