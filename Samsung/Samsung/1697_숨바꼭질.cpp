#include <iostream>
#include <queue>

using namespace std;

const int MAX = 100001;

int board[MAX] = { 0, };
int N, K;
int time = 1;
queue<int> q;

void bfs() {
	q.push(N);
	board[N] = 1;

	while (!q.empty()) {
		int next = q.front();
		q.pop();
		time = board[next];

		if (next == K) {
			cout << time - 1;
			return;
		}
		if (2 * next <= 100000 && board[2 * next] == 0 ) {
			q.push(2 * next);
			board[2 * next] = time + 1;
		}
		if (next + 1 <= 100000 && board[next + 1] == 0 ) {
			q.push(1+ next);
			board[1+ next] = time + 1;
		}
		if (next - 1 >= 0 && board[next - 1] == 0 ) {
			q.push(next-1);
			board[next - 1] = time + 1;
		}
	}
}

int main() {
	cin >> N >> K;

	bfs();

	return 0;
}