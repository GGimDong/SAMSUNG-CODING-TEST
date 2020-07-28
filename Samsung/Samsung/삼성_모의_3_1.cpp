/*
1
5
5 2 B C
4 2 A C
3 2 A B
4 0
7 0
*/
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

int T, N, ans;
int graph[10][10]; // A부터 0시작
int value[10];
int who[10]; // 0과 1 코치가 있음
bool visited[10] = {false};

void dfs(int node, int who_idx) {
	visited[node] = true;
	for (int i = 0; i < N; i++) {
		if (!visited[i] && who[i] == who_idx && graph[node][i] == 1) dfs(i, who_idx);
	}
}

bool is_grouped() {
	memset(visited, 0, sizeof(visited));
	// 먼저 첫빠따 0 잡아줌
	int s = -1;
	for (int i = 0; i < N; i++) {
		if (who[i] == 0) {
			s = i;
			break;
		}
	}
	if (s == -1) return false;
	dfs(s, 0);

	// 그 다음 첫 빠따 1 잡아줌
	s = -1;
	for (int i = 0; i < N; i++) {
		if (who[i] == 1) {
			s = i;
			break;
		}
	}
	if (s == -1) return false;
	dfs(s, 1);

	for (int i = 0; i < N; i++) if (!visited[i]) return false;
	return true;
}

void getResult(int idx) {
	if (idx >= N) {
		// 1. root check
		if (!is_grouped()) return;

		// 2. 차이 check
		int A = 0, B = 0;
		for (int i = 0; i < N; i++) {
			if (who[i] == 1) A += value[i];
			else B += value[i];
		}
		int result = abs(A - B);
		if (ans == -1 || ans > result) ans = result;
	}
	else {
		who[idx] = 1;
		getResult(idx+1);
		who[idx] = 0;
		getResult(idx + 1);
	}
}

int main() {
	cin >> T;
	char temp;
	int t;
	
	for (int test = 1; test <= T; test++) {
		memset(graph, 0, sizeof(graph));
		ans = -1;
		cin >> N;
		
		for (int i = 0; i < N; i++) {
			cin >> value[i] >>t;
			for (int j = 0; j < t; j++) {
				cin >> temp;
				int edge = temp - 'A';
				graph[i][edge] = 1;
				graph[edge][i] = 1;
			}
		}
		getResult(0);
		cout << "#" << test << " " << ans << endl;
	}
	
	return 0;
}