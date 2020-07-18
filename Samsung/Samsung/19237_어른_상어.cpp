/*
	1. 제발 문제좀 제대로 읽을 것!
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, M, K;

struct shark {
	int x;
	int y;
	int idx;
	int dir;
	bool is_dead = false;

	void set(int i, int j, int s_idx) {
		x = i;
		y = j;
		idx = s_idx;
	}
	void fight_dead() {
		if (!is_dead) 
			is_dead = true;
	}
};

struct map {
	int idx = 0;
	int time = 0;

	void time_passed() {
		if (time > 0)
			time--;
		if (time == 0)
			idx = 0;
	}

	void shark_passed(int s_idx) {
		idx = s_idx;
		time = K;
	}

};

map board[20][20];
int behave[401][5][4];
vector<shark> v;

int delta[5][2] = {
	{0, 0},
	{-1,0},	// 위
	{1,0},	// 아래
	{0,-1},	// 왼쪽
	{0,1}	// 오른쪽
};

bool cmp(const shark &s1, const shark &s2) {
	if (s1.idx < s2.idx)
		return true;
	else
		return false;
}

void move() {
	for (int i = 0; i < v.size(); i++) {
		shark Shark = v[i];
		if (!Shark.is_dead) {
			int idx = Shark.idx, x = Shark.x, y = Shark.y, dir = Shark.dir;
			bool is_moved = false;
			int next_dir, next_x, next_y;
			for (int j = 0; j < 4; j++) {
				int temp_dir = behave[idx][dir][j];
				next_x = x + delta[temp_dir][0], next_y = y + delta[temp_dir][1];
				if (next_x >= 0 && next_y >= 0 && next_x < N && next_y < N) {
					if(board[next_x][next_y].idx == 0) {
						is_moved = true;
						next_dir = temp_dir;
						break;
					}
					else if (!is_moved && board[next_x][next_y].idx == idx) {
						is_moved = true;
						next_dir = temp_dir;
					}
				}
			}
			next_x = x + delta[next_dir][0], next_y = y + delta[next_dir][1];
			v[i].x = next_x, v[i].y = next_y, v[i].dir = next_dir;
		}
	}
	for (int i = 0; i < v.size(); i++) {
		if (!v[i].is_dead) {
			int x = v[i].x, y = v[i].y, idx = v[i].idx;
			if (board[x][y].idx == 0 || board[x][y].idx >= idx) {
				board[x][y].idx = idx;
				board[x][y].time = K + 1;
			}
			else {
				v[i].fight_dead();
			}
		}
	}
	
}

void evaporate() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			board[i][j].time_passed();
}

bool check() {
	for (int i = 1; i < v.size(); i++)
		if (!v[i].is_dead)
			return false;
	
	return true;
}

int main() {
	cin >> N >> M >> K;
	
	int temp;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> temp;
			if (temp > 0) {
				board[i][j].shark_passed(temp);
				
				shark s;
				s.set(i, j, temp);
				v.push_back(s);
			}
		}

	sort(v.begin(),v.end(), cmp);
	
	for (int i = 0; i < M; i++) {
		cin >> temp;
		v[i].dir = temp;
	}

	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= 4; j++)
			for (int k = 0; k < 4; k++)
				cin >> behave[i][j][k];

	int ans = -1;
	
	for (int T = 1; T <= 1000; T++) {
		move();
		evaporate();

		if (check()) {
			ans = T;
			break;
		}
	}

	cout << ans;

	return 0;
}