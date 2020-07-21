/*
	자, 다시 생각잘하자.
	브루트 포스로 일을 할 때에는 무조건 for문을 돌릴때 왜 돌리는지 생각하자.
	만약 각 값에 들어갈 것들이 true false 였다면 사실 그냥 2개만 돌아가면 되는거였고
	branch가 3방향 이상 뻗어나간다면 두말할것 없이 for문을 그냥 돌릴 것이다.
	판단을 잘 하도록 하자.
*/
#include <iostream>
#include <cstdlib>
using namespace std;

const int MAX = 15;

int N;
int board[MAX][2];
bool visited[MAX];
int result = 0;
int ans = 0;

void doRecursion(int current) {
	if (current >= N) {
		if (ans < result) ans = result;
	}
	else {
		int dueDay = current + board[current][0];
		if (!visited[current] && dueDay <= N) {
			for (int i = current; i < dueDay; i++) visited[i] = true;
			result += board[current][1];
			doRecursion(dueDay);
			for (int i = current; i < dueDay; i++) visited[i] = false;
			result -= board[current][1];
		}
		doRecursion(current + 1);
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> board[i][0] >> board[i][1];
	}
	
	doRecursion(0);
	cout << ans;
	return 0;
}