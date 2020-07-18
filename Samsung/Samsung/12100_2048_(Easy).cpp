/*
	2048에서 이전의 움직임과 동일한 움직임
*/
#include <iostream>

using namespace std;
const int MAX = 20;
int N;
int origin[MAX][MAX];
int board[MAX][MAX];
int order[5];
int ans = -1;

int dx[4] = { 0,0,0,0 };
int dy[4] = { -1,1,0,0 };
// 1 왼쪽 2 오른쪽
void merge(int idx) {
	if (idx == 2) {
		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {
				
			}
		}
	}
	else {
		for (int x = N-1; x >= 0 ; x--) {
			for (int y = N-1; y >= 0; y--) {
				if (board[x + dx[idx]][y + dy[idx]] != 0 && board) {

				}
			}
		}
	}
}

void doRecursion(int current) {
	if (current >= 5) {
		
		

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				board[i][j] = origin[i][j];
			}
		}

		// TODO: order 값들을 가지고 계산
		for (int i = 0; i < 5; i++) {
			merge(order[i]);
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] > ans) {
					ans = board[i][j];
				}
			}
		}
	}
	else {
		for (int i = 1; i <= 4; i++) {
			if (current != 0 && order[current - 1] == i) continue;
			order[current] = i;
			doRecursion(current + 1);
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> origin[i][j];
		}
	}

	doRecursion(0);

	cout << ans;
	return 0;
}