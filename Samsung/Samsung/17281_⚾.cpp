#include <fstream>
#include <cstdio>
#include <vector>

#define MAX_INNING 50

using namespace std;

int board[MAX_INNING][9];

// 이닝 횟수
int N;
// 이 순서대로 이닝을 진행할 것임
vector<int> order;
int visited[9] = {0,};
// 시작점, 이닝마다 반복되야해서 전역 변수로 관리
int iteration = 0;
// 최고 점수
int max_point = 0;
int point = 0;

// out수 관리
int out = 0;
int playground[4] = { 0, };

void inning_changing() {
	// 경기장 비우기
	for (int i = 0; i < 4; i++)
		playground[i] = 0;
}

// 안타	: 1
// 2루타	: 2
// 3루타	: 3
// 홈런	: 4
// 아웃	: 0
void play_game() {
	point = 0;
	iteration = 0;
	
	for (int inning = 0; inning < N; inning++) {
		int out = 0;

		while (out < 3) {
			// OUT
			if (board[inning][order[iteration]] == 0) {
				out++;
			}
			// 안타
			else if (board[inning][order[iteration]] == 1) {
				if (playground[3]) {
					playground[3] = 0;
					point++;
				}
				if (playground[2]) {
					playground[2] = 0;
					playground[3] = 1;
				}
				if (playground[1]) {
					playground[1] = 0;
					playground[2] = 1;
				}
				playground[1] = 1;
			}
			// 2루타
			else if (board[inning][order[iteration]] == 2) {
				if (playground[3]) {
					playground[3] = 0;
					point++;
				}
				if (playground[2]) {
					playground[2] = 0;
					point++;
				}
				if (playground[1]) {
					playground[1] = 0;
					playground[3] = 1;
				}
				playground[2] = 1;
			}
			// 3루타
			else if (board[inning][order[iteration]] == 3) {
				if (playground[3]) {
					playground[3] = 0;
					point++;
				}
				if (playground[2]) {
					playground[2] = 0;
					point++;
				}
				if (playground[1]) {
					playground[1] = 0;
					point++;
				}
				playground[3] = 1;
			}
			// 홈런
			else if (board[inning][order[iteration]] == 4) {
				if (playground[3]) {
					playground[3] = 0;
					point++;
				}
				if (playground[2]) {
					playground[2] = 0;
					point++;
				}
				if (playground[1]) {
					playground[1] = 0;
					point++;
				}
				point++;
			}

			if (iteration == 8)
				iteration = 0;
			else
				iteration++;

		}
		inning_changing();
	}
	
	// 이닝이 다 끝나면 게임 종료
	if (point > max_point) max_point = point;
	
	return;
}

/*
	TODO: 순서 정하기 밑, dfs로 구현
*/
void dfs() {
	if (order.size() == 9) {
		if (order[3] != 0) {
			int temp = order[3];
			order[3] = 0;
			order[0] = temp;
		}
		play_game();

		return;
	}

	for (int i = 1; i < 9; i++) {
		
			if (!visited[i]) {
				visited[i] = 1;
				order.push_back(i);
				dfs();
				visited[i] = 0;
				order.pop_back();
			}
		
	}
}

int main() {
	ifstream input;
	input.open("input.txt");
	input >> N;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < 9; j++)
			input >> board[i][j];
	
	// 모든 선수들의 순서를 전부 고려한 iteration
	visited[0] = 1;
	order.push_back(0);
	dfs();
	
	printf("%d", max_point);

	return 0;
}