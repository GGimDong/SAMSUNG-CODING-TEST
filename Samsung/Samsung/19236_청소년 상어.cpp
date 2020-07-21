#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct fish {
	int x, y;
	bool is_dead = false;
}fishes[17];;

int board[4][4][2];
//				 1,	2,	3,	4,	5,	6,	7,	8
//				↑,	↖,	←,	↙,	↓,	↘,	→,	↗
int dx[9] = { 0,-1,	-1,	 0,	1,	 1,	 1,	 0,	-1 };
int dy[9] = { 0, 0,	-1,	-1,	-1,	 0,	 1,	 1,	 1 };
int ans = 0;

void print_board() {
	cout << "shark_num" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout<< board[i][j][0] <<" ";	
		}
		cout << endl;
	}
	
}

void dfs(int x, int y, int result) {
	// 해당 지역의 물고기 섭취 후...
	ans = max(result, ans);
	
	// fish move
	for (int i = 1; i <= 16; i++) {
		if (fishes[i].is_dead) continue; 
		int fish_x = fishes[i].x, fish_y = fishes[i].y, fish_dir = board[fish_x][fish_y][1];
		for (int j = 0; j < 8; j++) {
			int dir = fish_dir + j;
			if (dir > 8) dir = dir - 8;
			int next_x = fish_x + dx[dir], next_y = fish_y + dy[dir];
			if (next_x < 0 || next_y < 0 || next_x > 3 || next_y > 3 || board[next_x][next_y][0] == -1) continue;
			int swap_fish_num = board[next_x][next_y][0], swap_fish_dir = board[next_x][next_y][1];
			if (swap_fish_num == 0) swap_fish_dir = 0;

			board[next_x][next_y][0] = i;
			board[next_x][next_y][1] = dir;
			board[fish_x][fish_y][0] = swap_fish_num;
			board[fish_x][fish_y][1] = swap_fish_dir;

			fishes[i].x = next_x, fishes[i].y = next_y;
			fishes[swap_fish_num].x = fish_x, fishes[swap_fish_num].y = fish_y;
			
			break;
		}
	}
	
	//shark move
	// 먼저, 움직일 수 있는 타일들을 전부 다 구해놓음.
	vector<pair<int, int> > s_move;
	int s_dir = board[x][y][1];
	int s_dir_x = dx[s_dir], s_dir_y = dy[s_dir];
	for (int i = 1; i < 4; i++) {
		int next_x = x + s_dir_x * i, next_y = y + s_dir_y * i;
		if (next_x < 0 || next_y < 0 || next_x > 3 || next_y > 3 || board[next_x][next_y][0] == 0) continue;
		s_move.push_back(make_pair(next_x, next_y));
	}

	// 움직일 방향이 없으면 종료
	if (s_move.empty()) return;

	int copy_board[4][4][2];
	fish copy_fishes[17];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			copy_board[i][j][0] = board[i][j][0], copy_board[i][j][1] = board[i][j][1];
		}
	}
	for (int i = 1; i < 17; i++) {
		copy_fishes[i].x = fishes[i].x, copy_fishes[i].y = fishes[i].y, copy_fishes[i].is_dead = fishes[i].is_dead;
	}

	// 움직임이 가능하다면
	for (int i = 0; i < s_move.size(); i++) {
		int fish_num = board[s_move[i].first][s_move[i].second][0];
		board[x][y][0] = 0, board[x][y][1] = 0;
		board[s_move[i].first][s_move[i].second][0] = -1;
		fishes[fish_num].is_dead = true;
		
		//돌렸다가, 다시 복귀
		dfs(s_move[i].first,s_move[i].second, result+fish_num);

		fishes[fish_num].is_dead = false;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[i][j][0] = copy_board[i][j][0], board[i][j][1] = copy_board[i][j][1];
			}
		}
		for (int i = 1; i < 17; i++) {
			fishes[i].x = copy_fishes[i].x, fishes[i].y = copy_fishes[i].y, fishes[i].is_dead = copy_fishes[i].is_dead;
		}
	}

}

int main() {
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++) {
			cin >> board[i][j][0] >> board[i][j][1];
			fishes[board[i][j][0]].x = i, fishes[board[i][j][0]].y = j;
		}
	}

	int fish_num = board[0][0][0];
	board[0][0][0] = -1;

	fishes[fish_num].is_dead = true;

	dfs(0, 0, fish_num);
	cout << ans;
	return 0;
}