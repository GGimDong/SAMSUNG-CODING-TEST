#include <iostream>
#include <vector>

#define MAX 102

using namespace std;

struct point {
	int x;
	int y;
};

// 집과 목적지

int p_idx;
int T, N, x, y;
vector<int> graph[MAX];

int ans = -1;
bool visited[MAX] = { false, };

void bfs(int current) {
	if (current == p_idx) {
		ans = 1;
		return;
	}
	else {
		for (int i = 0; i <= p_idx; i++) {
			if (ans!=1 && current != i && graph[current][i] <= 1000 && !visited[i]) {
				visited[i] = true;
				bfs(i);
				visited[i] = false;
			}
		}
	}

}

void clear() {
	for (int i = 0; i <= p_idx; i++)
		visited[i] = false;
	ans = -1;
}

int main() {
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		vector<point> p;
		point temp;
		
		cin >> temp.x >> temp.y;
		p.push_back(temp);

		for (int j = 0; j < N; j++) {
			cin >> temp.x >> temp.y;
			p.push_back(temp);
		}

		cin >> temp.x >> temp.y;
		p.push_back(temp);
		p_idx = N + 1;

		
		// graph 만들기
		for (int j = 0; j <= p_idx; j++) {
			for (int k = j+1; k <= p_idx; k++) {
				int len = abs(p[j].x-p[k].x) + abs(p[j].y - p[k].y);
				graph[j][k] = len;
				graph[k][j] = len;
			}
		}
		
		visited[0] = true;
		bfs(0);
		
		if (ans == -1)
			cout << "sad" << endl;
		else
			cout << "happy" << endl;

		clear();
	}

	return 0;
}