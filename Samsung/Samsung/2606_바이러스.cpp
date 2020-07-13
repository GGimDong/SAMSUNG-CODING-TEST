#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 101;
vector<int> graph[MAX];

int N, E;

bool visited[MAX] = {false, };

void calc() {
	int ans = 0;
	for(int i = 1;i <= N;i++){
		if (visited[i] && i != 1) {
			ans++;
		}
	}
	cout << ans;
}


void dfs(int x) {
	visited[x] = true;

	for (int i = 0; i < graph[x].size(); i++) {
		int y = graph[x][i];
		if (!visited[y])
			dfs(y);
	}
}

int main() {
	cin >> N >> E;

	int a, b;
	for (int i = 0; i < E; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 0; i < N; i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	dfs(1);
	calc();
	return 0;
}