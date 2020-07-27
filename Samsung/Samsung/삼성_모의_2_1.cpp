/*
1
4 6 2
0 0 2 1 2 0
0 0 0 1 2 0
1 1 0 0 1 1
0 2 2 0 0 2
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 100;

int arr[MAX][MAX]; // 0�� �ƹ��͵� ����, 1�� ��, 2�� ��ǻ�� ��
int t_arr[MAX][MAX];
int defuser[10][3]; //	defuser[x][y] x��° ��ǻ��, y: (��������,x,y)

int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int T, N, M, K, defuserIdx;	// defuser�� 0~9����
int ans;

void simulate() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) 
			t_arr[i][j] = arr[i][j];
		
	queue<pair<int, int> > q;
	for (int i = 0; i < defuserIdx; i++) { 
		if (defuser[i][0] == 1) {
			q.push(make_pair(defuser[i][1], defuser[i][2]));
			t_arr[defuser[i][1]][defuser[i][2]] = 1;
		}
		else {
			t_arr[defuser[i][1]][defuser[i][2]] = 0;
		}
	}

	while (!q.empty()) {
		pair<int, int> next = q.front();
		q.pop();
		int x = next.first, y = next.second;
		int time = t_arr[x][y];

		for (int i = 0; i < 4; i++) {
			int n_x = x + dir[i][0], n_y = y + dir[i][1];
			if (n_x < 0 || n_y < 0 || n_x >= N || n_y >= M || t_arr[n_x][n_y] != 0) continue;
			t_arr[n_x][n_y] = time + 1;
			q.push(make_pair(n_x, n_y));
		}
	}

	// ��� ��ǻ���� �������� ���� �ִµ�, ��ǻ���ֵ��� ���� �� 1��
	for (int i = 0; i < defuserIdx; i++) t_arr[defuser[i][1]][defuser[i][2]] = 1;

	int MAX_T = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (t_arr[i][j] == 0) return;
			else {
				if (t_arr[i][j] > MAX_T) MAX_T = t_arr[i][j];
			}
		}
	}
	MAX_T--;
	if (ans == -1 || ans > MAX_T) ans = MAX_T;
}

void getResult(int idx, int start) {
	if (idx >= K) {
		// ��⸦ �۶߷�����
		/*
		for (int i = 0; i < defuserIdx; i++) {
			cout << defuser[i][0] <<" ";
		}cout << endl;
		system("pause");*/
		simulate();

	}
	else {
		for (int i = start; i < defuserIdx; i++) {
			if (defuser[i][0] == 0) {
				defuser[i][0] = 1;
				getResult(idx + 1, i);
				defuser[i][0] = 0;
			}
		}
	}
}

int main() {
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		ans = -1;
		scanf("%d %d %d", &N, &M, &K);
		defuserIdx = 0;

		for (int i = 0; i < N; i++){
			for (int j = 0; j < M; j++) {
				scanf("%d", &arr[i][j]);
				if (arr[i][j] == 2) {
					defuser[defuserIdx][0] = 0, defuser[defuserIdx][1] = i, defuser[defuserIdx++][2] = j;
				}
				else if (arr[i][j] == 1) {
					arr[i][j] = -1;
				}
			}
		}

		/* // ��ǻ�� ���� Ȯ�ο�
		for (int i = 0; i < defuserIdx; i++) {
			cout << i + 1 << ": " << defuser[i][1] << defuser[i][2] << endl;
		}
		system("pause");
		*/
		getResult(0, 0);
		
		printf("#%d %d\n", test_case, ans);
	}
	return 0;
}