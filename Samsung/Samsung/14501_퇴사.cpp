/*
	��, �ٽ� ����������.
	���Ʈ ������ ���� �� ������ ������ for���� ������ �� �������� ��������.
	���� �� ���� �� �͵��� true false ���ٸ� ��� �׳� 2���� ���ư��� �Ǵ°ſ���
	branch�� 3���� �̻� ������ٸ� �θ��Ұ� ���� for���� �׳� ���� ���̴�.
	�Ǵ��� �� �ϵ��� ����.
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