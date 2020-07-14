#include <iostream>
#include <queue>

using namespace std;

const int MAX = 1000001;
int visited[MAX] = { 0, };

int F, S, G, U, D;
int ans = -1;

int time;

void bfs() {
	queue<int> q;

	q.push(S);
	visited[S] = 1;
	
	while (!q.empty()) {
		int next = q.front();
		q.pop();
		time = visited[next];

		if (next == G) {
			ans = time - 1;
			return;
		}

		if (next + U <= F && visited[next + U] == 0) {
			q.push(next + U);
			visited[next + U] = time + 1;
		}

		if (next - D > 0 && visited[next - D] == 0) {
			q.push(next - D);
			visited[next - D] = time + 1;
		}
	}
}

int main() {
	cin >> F >> S >> G >> U >> D;

	bfs();

	if (ans == -1)
		cout << "use the stairs";
	else
		cout << ans;

	return 0;
}