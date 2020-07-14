#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 100;

int N, E, A, B;
int time = 0;
int ans = -1;

vector<int> graph[MAX];
int visited[MAX] = { 0, };

void bfs() {
	queue<int> q;

	visited[A] = 1;
	q.push(A);
	
	while (!q.empty()) {
		int next = q.front();
		q.pop();
		time = visited[next];
		if (next == B) {
			ans = time - 1;
			return;
		}

		for (int i = 0; i < graph[next].size(); i++) {
			int next_n = graph[next][i];
			if (visited[next_n] == 0) {
				visited[next_n] = time+1;
				q.push(next_n);
			}
		}

	}
}

int main() {
	cin >> N;
	cin >> A >> B;
	cin >> E;

	int a, b;
	for (int i = 0; i < E; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 0; i < N; i++) 
		sort(graph[i].begin(), graph[i].end());
	
	bfs();

	cout << ans;

	return 0;
}