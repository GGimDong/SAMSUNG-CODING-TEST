#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

int N, E, S;

const int MAX = 1001;

vector<int> graph[MAX];
bool visited[MAX] = {false, };

void dfs(int x) {
	visited[x] = true;
	cout << x << " ";

	for (int i = 0; i < graph[x].size(); i++) {
		int y = graph[x][i];
		if (!visited[y]) {
			dfs(y);
		}
	}
}

void doRecursionBFS(int s) {
	queue<int> q;
	bool check[MAX] = {false, };

	q.push(s);
	check[s] = true;
	cout << s << " ";

	while (!q.empty()) {
		int current = q.front();
		q.pop();
		
		for (int i = 0; i < graph[current].size(); i++) {
			int next = graph[current][i];
			if (!check[next]) {
				q.push(next);
				check[next] = true;
				cout << next << " ";
			}
		}
	}
	cout << endl;
}

int main() {
	cin >> N >> E >> S;

	int a, b;
	for (int i = 0; i < E; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 0; i < N; i++)
		sort(graph[i].begin(), graph[i].end());

	dfs(S);
	cout << endl;
	doRecursionBFS(S);

	return 0;
}