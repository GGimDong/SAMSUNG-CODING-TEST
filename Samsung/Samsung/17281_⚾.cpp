#include <fstream>
#include <cstdio>
#include <vector>

#define MAX_INNING 50

using namespace std;

int board[MAX_INNING][9];

// �̴� Ƚ��
int N;
// �� ������� �̴��� ������ ����
vector<int> order;
int visited[9] = {0,};
// ������, �̴׸��� �ݺ��Ǿ��ؼ� ���� ������ ����
int iteration = 0;
// �ְ� ����
int max_point = 0;
int point = 0;

// out�� ����
int out = 0;
int playground[4] = { 0, };

void inning_changing() {
	// ����� ����
	for (int i = 0; i < 4; i++)
		playground[i] = 0;
}

// ��Ÿ	: 1
// 2��Ÿ	: 2
// 3��Ÿ	: 3
// Ȩ��	: 4
// �ƿ�	: 0
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
			// ��Ÿ
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
			// 2��Ÿ
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
			// 3��Ÿ
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
			// Ȩ��
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
	
	// �̴��� �� ������ ���� ����
	if (point > max_point) max_point = point;
	
	return;
}

/*
	TODO: ���� ���ϱ� ��, dfs�� ����
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
	
	// ��� �������� ������ ���� ����� iteration
	visited[0] = 1;
	order.push_back(0);
	dfs();
	
	printf("%d", max_point);

	return 0;
}