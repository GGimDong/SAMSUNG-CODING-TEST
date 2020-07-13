/*
1. ���� ������.
2. ���� ���� ����� �����Ѵ�. 
*/

#include <iostream>

using namespace std;

const int MAX = 20;

int N, team_num;
int board[MAX][MAX];
int ans = -1; 

// 1�̸� ��ŸƮ��, 0�̸� ��ũ��
int team[MAX] = {0, };

int pos(int n) {
	if (n < 0)
		return -1 * n;
	return n;
}

void calcPoint() {
	int team_a=0, team_b = 0;
	int gap;
	for (int i = 0; i < N; i++) {
		if (team[i] == 1) {
			for (int j = 0; j < N; j++) {
				if (team[j] == 1)
					team_a += board[i][j];
			}
		}
		else if (team[i] == 0) {
			for (int j = 0; j < N; j++) {
				if (team[j] == 0)
					team_b += board[i][j];
			}
		}
	}

	gap = pos(team_a - team_b);
	if (ans == -1 || gap < ans)
		ans = gap;

}

// ���⼭ current�� '��ŸƮ ���� �ο���'
void doRecursion(int current, int idx) {
	if (current >= team_num)
		calcPoint();
	else {
		for (int i = idx; i < N; i++){
			if (team[i] == 0) {
				team[i] = 1;
				doRecursion(current+1, i);
				team[i] = 0;
			}
		}
	}
}

int main() {
	cin >> N;
	team_num = N / 2;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> board[i][j];

	doRecursion(0, 0);

	cout << ans; 
	return 0;
}
