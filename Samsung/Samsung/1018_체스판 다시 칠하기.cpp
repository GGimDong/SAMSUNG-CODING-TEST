#include <iostream>

using namespace std;

const int MAX = 50;

int N, M;
char board[MAX][MAX];
int ans = -1;

int small(int a, int b) {
	if (a < b) return a;
	else return b;
}

void calc(int x, int y) {
	// 왼쪽 위가 B로 시작하는 경우
	int temp_ans_1 = 0;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0 && board[x + i][y + j] != 'B')
				temp_ans_1++;
			else if ((i + j) % 2 == 1 && board[x + i][y + j] != 'W')
				temp_ans_1++;
		}
	// 왼쪽 위가 W로 시작하는 경우
	int temp_ans_2 = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0 && board[x + i][y + j] != 'W')
				temp_ans_2++;
			else if ((i + j) % 2 == 1 && board[x + i][y + j] != 'B')
				temp_ans_2++;
		}
	int temp_ans = small(temp_ans_1,temp_ans_2);
	if (ans == -1 || temp_ans < ans)
		ans = temp_ans;
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> board[i][j];

	for (int i = 0; i <= N - 8; i++)
		for (int j = 0; j <= M - 8; j++)
			calc(i, j);

	cout << ans;

	return 0;
}