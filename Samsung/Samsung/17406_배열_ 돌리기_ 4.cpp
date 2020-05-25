#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_SIZE 50
#define MAX_K 100

using namespace std;

int board[MAX_SIZE][MAX_SIZE];
int origin_board[MAX_SIZE][MAX_SIZE];
int temp[MAX_SIZE][MAX_SIZE];

int N, M, K;
int min_result=999;

vector<int> order;
int c[MAX_K];
int r[MAX_K];
int s[MAX_K];

void print_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			printf("%d ", temp[i][j]);
		printf("\n");
	}
	printf("\n");
}

void init() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			board[i][j] = origin_board[i][j];
}

void rotate(int r, int c, int s) {
	for (int i = 0; i <= s; i++) {
		// 일단 모서리들 전부 고고륑
		if (i == 0) {
			temp[r][c] = board[r][c];
		}
		else {
			temp[r - i][c - i + 1] = board[r - i][c - i];
			temp[r - i + 1][c + i] = board[r - i][c + i];
			temp[r + i - 1][c - i] = board[r + i][c - i];
			temp[r + i][c + i - 1] = board[r + i][c + i];
			
			for (int j = 0; j < 2 * i; j++) {
				/* 위 */ temp[r - i][c - i + j + 1] = board[r - i][c - i + j];
				/*오른*/ temp[r - i + j + 1][c + i] = board[r - i + j][c + i];
				/* 밑 */ temp[r + i][c + i - j-1] = board[r + i][c + i-j];
				/* 왼 */ temp[r + i - j-1][c - i] = board[r + i - j][c - i];
			}
		}	
	}
	
	for (int i = r - s; i <= r + s; i++)
		for (int j = c - s; j <= c + s; j++)
			board[i][j] = temp[i][j];
}

void calc() {
	int result = 0;
	for (int i = 0; i < N; i++) {
		result = 0;
		for (int j = 0; j < M; j++) {
			result += board[i][j];
		}
		if (result < min_result)
			min_result = result;
	}
}


int main() {
	// output: 12
	ifstream input;
	input.open("input/Array_rotate_4/input.txt");
	input >> N >> M >> K;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			input >> board[i][j];
			origin_board[i][j] = board[i][j];
		}
		
	for (int i = 0; i < K; i++) {
		order.push_back(i);
		input >> r[i] >> c[i] >> s[i];
	}

	// next_permutation을 통해서 다음 순열 구하기
	do {
		// 모든 순열에 대해서 계산함
		for (int i = 0; i < K; i++) 
			rotate(r[order[i]]-1, c[order[i]]-1, s[order[i]]);
		
		calc();
		init();
	} while (next_permutation(order.begin(), order.end()));

	printf("%d", min_result);

	return 0;
}