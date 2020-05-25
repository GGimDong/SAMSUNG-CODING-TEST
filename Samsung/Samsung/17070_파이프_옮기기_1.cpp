#include <cstdio>
#include <fstream>
#define MAX_SIZE 16

using namespace std;

int board[MAX_SIZE][MAX_SIZE];
int N;
// 0: ����, 1: ����, 2: 45��ȸ��
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

	// ������Ʈ ���� Ȯ�� �� �ൿ�� �����ؼ� dfs ����
	if (state == 0) {// ������ ����
		// �������� ����ٸ� ���������� ���η� ��ĭ ����
		if (r + 1 != N && board[c][r + 1] == 0) {
				state = 0;
				dfs(c,r+1);
				state = pre_state;
		}
		// ������ ���� ����ٸ� ȸ������ �̵�
		if (r + 1 != N && c + 1 != N && board[c + 1][r + 1] == 0 && board[c + 1][r] == 0 && board[c][r + 1] == 0) {
			state = 2;
			dfs(c+1, r + 1);
			state = pre_state;
		}
	}
	else if (state == 1) { // ������ ����
		// �ϴ��� ������� �ϴ����� ����
		if (c + 1 != N && board[c+1][r] == 0) {
			state = 1;
			dfs(c+1, r);
			state = pre_state;
		}
		// �ϴ� ���� ����ٸ�
		if (r + 1 != N && c + 1 != N && board[c + 1][r + 1] == 0 && board[c + 1][r] == 0 && board[c][r + 1] == 0) {
			state = 2;
			dfs(c + 1, r + 1);
			state = pre_state;
		}
	}
	else {// state�� 2, ȸ���� ����
		// �������� ����ٸ� ���������� ���η� ��ĭ ����
		if (r + 1 != N && board[c][r + 1] == 0) {
			state = 0;
			dfs(c, r + 1);
			state = pre_state;
		}
		// �ϴ��� ������� �ϴ����� ����
		if (c + 1 != N && board[c + 1][r] == 0) {
			state = 1;
			dfs(c + 1, r);
			state = pre_state;
		}
		// �ϴ� ���� ����ٸ�
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

	// �����ִ� ������, �������� 2, ���� 1��
	dfs(0,1);
	printf("%d", num);
	return 0;
}