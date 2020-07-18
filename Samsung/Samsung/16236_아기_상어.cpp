/*
	1. 우선순위가 왼쪽 위에서 오른쪽 아래일때는, 그냥 BFS 퍼지듯이 한다고 한들 이게 되는 것이 아니였군...
	직접 다 BFS돌리고 차라리 위에서 아래로 확인하자....

	2. 사소한 조건이라도 그냥 달아놓자, 이게 error가 될지 debuging으로 잡힐지 모르니까....

*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int board[20][20];
int visited[20][20];
int dx[4] = { -1,0,0,1 };
int dy[4] = { 0,-1,1,0 };

struct shark {
	int x, y, size, eaten_fish;
};

shark baby;

int main() {
	int num_of_fish = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 9) {
				baby.x = i, baby.y = j, baby.size = 2, baby.eaten_fish = 0;
			}
			else if (board[i][j] != 0) {
				num_of_fish++;
			}
		}
	}

	int T = 0;
	while (num_of_fish > 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visited[i][j] = 0;
			}
		}

		queue<pair<int, int> > q;
		vector<pair<int, int> > candidate;
		int step; 
		int target_step = -1;
		q.push(make_pair(baby.x, baby.y));
		visited[baby.x][baby.y] = 1;
		
		while (!q.empty()) {
			pair<int, int> pos = q.front();
			q.pop();
			int x = pos.first, y = pos.second;
			step = visited[x][y];

			if (target_step == -1 && board[x][y] > 0 && board[x][y] < 7 && board[x][y] < baby.size) {
				target_step = step;
			}

			if (target_step == step && board[x][y] > 0 && board[x][y] < 7 && board[x][y] < baby.size) {
				candidate.push_back(pos);
			}

			for (int i = 0; i < 4; i++) {
				int next_x = x + dx[i], next_y = y + dy[i];
				if (next_x >= 0 && next_y >= 0 && next_x < N && next_y < N && baby.size >= board[next_x][next_y] && visited[next_x][next_y] == 0) {
					visited[next_x][next_y] = step + 1;
					q.push(make_pair(next_x, next_y));
				}
			}
		}

		if (target_step == -1) {
			break;
		}
		sort(candidate.begin(), candidate.end());
		pair<int, int> target;
		target = candidate.front();

		int x = target.first, y = target.second;
		T += (target_step - 1);
		board[x][y] = 9, board[baby.x][baby.y] = 0;
		baby.x = x, baby.y = y;
		num_of_fish--, baby.eaten_fish++;

		if (baby.eaten_fish == baby.size) {
			baby.size++, baby.eaten_fish = 0;
		}
	}
	cout << T;
	return 0;
}