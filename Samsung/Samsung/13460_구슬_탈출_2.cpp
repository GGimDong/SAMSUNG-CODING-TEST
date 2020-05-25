#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
int N, M;
char board[10][10];
char temp_board[10][10];

vector<int> v; // 1 2 3 4 상 하 좌 우
int min_value = -1;

void print_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cout << temp_board[i][j];
		cout << endl;
	}
	return;
}

void copy_board() {
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++)
			temp_board[i][j] = board[i][j];
	return;
}

void move(int op) {
	int t_i, t_j;

	if(op ==1 || op == 3)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				if (temp_board[i][j] == 'R' || temp_board[i][j] == 'B') {
					t_i = i;
					t_j = j;
					if (op == 1) {
						while (temp_board[t_i - 1][t_j] == '.' || temp_board[t_i - 1][t_j] == 'O') {
							if (temp_board[t_i - 1][t_j] == 'O') {
								temp_board[t_i][t_j] = '.';
								break;
							}
								temp_board[t_i - 1][t_j] = temp_board[t_i][t_j];
								temp_board[t_i][t_j] = '.';
								t_i--;
						}
					}
					if (op == 3) {
						while (temp_board[t_i][t_j - 1] == '.' || temp_board[t_i][t_j - 1] == 'O') {
							if (temp_board[t_i][t_j - 1] == 'O') {
								temp_board[t_i][t_j] = '.';
								break;
							}
							temp_board[t_i][t_j - 1] = temp_board[t_i][t_j];
							temp_board[t_i][t_j] = '.';
							t_j--;
						}
					}
				}
			}
	else if(op ==2 || op ==4)
		for (int i = N-1; i >= 0; i--)
			for (int j = M - 1; j >= 0; j--) {
				if (temp_board[i][j] == 'R' || temp_board[i][j] == 'B') {
					t_i = i;
					t_j = j;
					if (op == 2) {
						while (temp_board[t_i + 1][t_j] == '.' || temp_board[t_i + 1][t_j] == 'O') {
							if (temp_board[t_i + 1][t_j] == 'O') {
								temp_board[t_i][t_j] = '.';
								break;
							}
							temp_board[t_i + 1][t_j] = temp_board[t_i][t_j];
							temp_board[t_i][t_j] = '.';
							t_i++;
						}
					}
					else if (op == 4){
						while (temp_board[t_i][t_j + 1] == '.' || temp_board[t_i][t_j + 1] == 'O') {
							if (temp_board[t_i][t_j + 1] == 'O') {
								temp_board[t_i][t_j] = '.';
								break;
							}
							temp_board[t_i][t_j + 1] = temp_board[t_i][t_j];
							temp_board[t_i][t_j] = '.';
							t_j++;
						}
					}
				}
			}
	return;
}

int do_operation(int op) {
	// temp_board 의 값들을 op 에 맞게 동작.
	
	move(op);
	// 파란 구슬이 존재하는지 검사
	int is_blue = -1;
	int is_red = -1;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (temp_board[i][j] == 'B') is_blue = 1;
			if (temp_board[i][j] == 'R') is_red = 1;
		}
	// 파란 구슬이 없으면 무조건 실패
	if (is_blue == -1)
		return -1;

	// 빨간 구슬이 없으면 이는 성공
	if (is_red == -1)
		return 1;

	return 0;
}

void start_operation() {
	copy_board();
	for (int i = 0; i < v.size(); i++) {
		int result = do_operation(v[i]);
		if (result == 1) {
			// 빨간 구슬만 쏙 나온 경우
			int temp_min_value = i + 1;

			if(min_value > temp_min_value || min_value == -1)
				min_value = temp_min_value;
			break;
		}
		else if (result == -1) // 어떻게든 파란 구슬도 쏙 나온 경우
			break;
	}
}

void operation_order() {
	if (v.size() == 10) {
		start_operation();
		return;
	}

	v.push_back(1);
	operation_order();
	v.pop_back();

	v.push_back(2);
	operation_order();
	v.pop_back();

	v.push_back(3);
	operation_order();
	v.pop_back();

	v.push_back(4);
	operation_order();
	v.pop_back();

	return;
}

int main() {
	ifstream input;
	input.open("input/input.txt");
	
	input >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) 
			input >> board[i][j];
	
	operation_order();
	
	cout << min_value;
	return 0;
}