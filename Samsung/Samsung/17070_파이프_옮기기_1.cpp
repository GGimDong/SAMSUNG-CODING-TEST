#include <cstdio>
#include <fstream>
#define MAX_SIZE 16

using namespace std;

int board[MAX_SIZE][MAX_SIZE];
int N;
// 0: 가로, 1: 세로, 2: 45도회전
int state=0;
int num = 0;

void print_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", board[i][j]);
		printf("\n");
	}
}

void dfs(int c, int r){
	if (c == N - 1 && r == N - 1) {
		num++;
		return;
	}
	int pre_state = state;

	// 스태이트 먼저 확인 후 행동을 결정해서 dfs 돌림
	if (state == 0) {// 가로인 상태
		// 오른쪽이 비었다면 오른쪽으로 가로로 한칸 ㄱㄱ
		if (r + 1 != N && board[c][r + 1] == 0) {
				state = 0;
				dfs(c,r+1);
				state = pre_state;
		}
		// 오른쪽 밑이 비었다면 회전으로 이동
		if (r + 1 != N && c + 1 != N && board[c + 1][r + 1] == 0 && board[c + 1][r] == 0 && board[c][r + 1] == 0) {
			state = 2;
			dfs(c+1, r + 1);
			state = pre_state;
		}
	}
	else if (state == 1) { // 세로인 상태
		// 하단이 비었으면 하단으로 ㄱㄱ
		if (c + 1 != N && board[c+1][r] == 0) {
			state = 1;
			dfs(c+1, r);
			state = pre_state;
		}
		// 하단 밑이 비었다면
		if (r + 1 != N && c + 1 != N && board[c + 1][r + 1] == 0 && board[c + 1][r] == 0 && board[c][r + 1] == 0) {
			state = 2;
			dfs(c + 1, r + 1);
			state = pre_state;
		}
	}
	else {// state가 2, 회전한 상태
		// 오른쪽이 비었다면 오른쪽으로 가로로 한칸 ㄱㄱ
		if (r + 1 != N && board[c][r + 1] == 0) {
			state = 0;
			dfs(c, r + 1);
			state = pre_state;
		}
		// 하단이 비었으면 하단으로 ㄱㄱ
		if (c + 1 != N && board[c + 1][r] == 0) {
			state = 1;
			dfs(c + 1, r);
			state = pre_state;
		}
		// 하단 밑이 비었다면
		if (r + 1 != N && c + 1 != N && board[c + 1][r + 1] == 0 && board[c + 1][r] == 0 && board[c][r + 1] == 0) {
			state = 2;
			dfs(c + 1, r + 1);
			state = pre_state;
		}
	}
}

int main() {
	
	/* 
	input	1 2 3 4
	output	1 3 0 13
	*/
	ifstream input;
	input.open("input/Pipe/input4.txt");
	input >> N;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			input >> board[i][j];

	// 원래있던 파이프, 파이프가 2, 벽이 1임
	dfs(0,1);
	printf("%d", num);
	return 0;
}