/*
x축은 → 방향, y축은 ↓ 방향
1세대 드래곤 커브는 0세대 드래곤 커브를 끝 점을 기준으로 
시계 방향으로 90도 회전시킨 다음 0세대 드래곤 커브의 끝 점에 붙인 것
*/
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#define MAX_N 20


using namespace std;

struct point {
	int x;
	int y;
};


/*
	Direction
	0: x좌표가 증가하는 방향 (→)
	1: y좌표가 감소하는 방향 (↑)
	2: x좌표가 감소하는 방향 (←)
	3: y좌표가 증가하는 방향 (↓)
*/
int diretion[4][2] = { 
	{0, 1}, 
	{-1, 0}, 
	{0, -1}, 
	{1, 0} 
};

int n;
int x[MAX_N]; int y[MAX_N];	// Start point
int d[MAX_N];				// start_dir
int g[MAX_N];				// Generation

int board[101][101];
int ans = 0;

void find() {
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			if (board[i][j] == 1 && board[i+1][j] == 1 && board[i][j+1] == 1 && board[i+1][j+1] == 1) ans++;
}

void set_point(int x, int y) {
	if (x < 0 || x > 100) return;
	if (y < 0 || y > 100) return;

	board[y][x] =1;
	return;
}

void find_next_point(int &x, int &y, int d) {
	y += diretion[d][0];
	x += diretion[d][1];
	return;
}

void generate_dragon(vector<int> dirs, int start_x, int start_y) {
	int x = start_x;
	int y = start_y;
	set_point(x, y);
	for (int i = 0; i < dirs.size(); i++) {
		
		find_next_point(x, y, dirs[i]);
		set_point(x, y);
	}
	return;
}

int next_dir(int dir) {
	return (dir + 1) % 4;
}

void generate_direction_set(vector<int> &dirs, int gen, int max_gen) {
	if (gen == max_gen)
		return;
	
	for (int i = dirs.size() - 1; i >= 0; i--) 
		dirs.push_back(next_dir(dirs[i]));
	
	generate_direction_set(dirs, gen + 1, max_gen);
}

int main() {
	ifstream input;
	input.open("input/input.txt");


	input >> n;
	for (int i = 0; i < n; i++)
		input >> x[i] >> y[i] >> d[i] >> g[i];

	for (int i = 0; i < n; i++) {
		vector<int> dirs;
		dirs.push_back(d[i]);
		generate_direction_set(dirs, 0, g[i]);
		generate_dragon(dirs, x[i], y[i]);
	}
	find();
	cout << ans;
	return 0;
}