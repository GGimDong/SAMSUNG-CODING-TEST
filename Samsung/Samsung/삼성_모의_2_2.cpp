/*
1
7
1 1 0 5 9 1 3
5 2 3 1 6 2 2
7 0 5 1 1 4 1
4 0 0 3 1 2 1
0 0 1 6 7 0 1
3 8 1 2 6 1 8
7 6 1 0 5 0 8
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 20;

struct Player {
	int x, y; 
	int level = 2; // 낮은 레벨은 kill가능, 같은 레벨은 지나가기가 가능
	int kill_num = 0;
	void kill() {
		kill_num++;
		if (kill_num == level) {
			kill_num = 0;
			level++;
		}
	}
}player;

int arr[MAX][MAX];
int t_arr[MAX][MAX];	// 0은 지나갈수 있는 구간, -1은 못 지나감, -2 는 적
int T, N, ans;
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };

int findEnemy() {
	// 1. 가장 가까운 적을 탐색한다.
	// t_arr를 상황에 맞게 재구성
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			t_arr[i][j] = 0;
		}
	}

	int result = -1;
	queue<pair<int, int> > q;
	q.push(make_pair(player.x, player.y));
	t_arr[player.x][player.y] = 1;

	while (!q.empty()) {
		pair<int, int> next = q.front();
		q.pop();
		int x = next.first, y = next.second;
		int t = t_arr[x][y];
		// 와 시발 ㅋㅋㅋㅋ t에서 뻑날뻔
		if (result == -1 && arr[x][y] > 0 && arr[x][y] < player.level && t!= 1) result = t;

		for (int i = 0; i < 4; i++) {
			int n_x = x + dir[i][0], n_y = y + dir[i][1];
			if (n_x < 0 || n_y < 0 || n_x >= N || n_y >= N || arr[n_x][n_y] > player.level || t_arr[n_x][n_y] != 0) continue;
			t_arr[n_x][n_y] = t+1;
			q.push(make_pair(n_x,n_y));
		}
	}

	if(result == -1) return -1;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (t_arr[i][j] == result && arr[i][j] > 0 && arr[i][j] < player.level) {
				arr[player.x][player.y] = 0;
				player.x = i, player.y = j;
				arr[player.x][player.y] = 9;
				ans += (result - 1);
				player.kill();
				return 1;
			}
		}
	}
}

int main() {
	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++) {
		ans = 0;
		cin >> N;
		player.level = 2, player.kill_num = 0;
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> arr[i][j];
				if (arr[i][j] == 9) {
					player.x = i;
					player.y = j;
				}
			}
		}
		while (1) if (findEnemy() == -1) break;

		printf("#%d %d\n", test_case, ans);
	}
	return 0;
}