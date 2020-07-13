/*
1. 1인 곳을 찾으면, 
2. 그 지점을 기준으로 DFS하여 전부 번호를 매겨버리자
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int dir[4][2] = {
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}
};

const int MAX = 25;

int N;
char line[MAX];
int board[MAX][MAX] = {0,};
vector<int> v;

int num = 0;

void dfs(int x, int y, int output) {
	int idx = output - 1;
	v[idx]++;
	board[x][y] = output;
	for (int i = 0; i < 4; i++) {
		int dx = dir[i][0];
		int dy = dir[i][1];
		if (board[x + dx][y + dy] == -1 && x + dx >= 0 && y +dy >= 0 && x+ dx < N && y + dy < N)
			dfs(x + dx, y + dy, output);
	}
}

int main() {
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		cin >> line;
		for (int j = 0; j < N; j++)
			if (line[j] == '0')
				board[i][j] = 0;
			else if (line[j] == '1')
				board[i][j] = -1;
	}
	
	
	// 마킹
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (board[i][j] == -1) {
				v.push_back(0);
				num++;
				dfs(i, j, num);
			}

	cout << num << endl;
	sort(v.begin(), v.end());
	for (int i = 0; i< v.size(); i++)
		cout << v[i] << endl;
	
	return 0;
}