#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#define MAX 102

using namespace std;

struct point {
	int x;
	int y;
};

// 목적지 idx
int p_idx;
int T, N, x, y;
unsigned int graph[MAX][MAX];

int ans = -1;
bool visited[MAX] = { false, };

bool bfs() {
	queue<int> q;

	q.push(0);
	visited[0] = true;

	while (!q.empty()) {
		int next = q.front();
		q.pop();
		
		if (visited[p_idx]) 
			return true;
		
		for (int i = 0; i <= p_idx; i++) {
			int edge = graph[next][i];
			if (!visited[i] && edge <=1000) {
				visited[i] = true;
				q.push(i);
			}
		}
	}

	return false;
}

void clear() {
	for (int i = 0; i <= p_idx; i++) {
		visited[i] = false;
	}
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
			for (int k = 0; k <= p_idx; k++) {
				int len = abs(p[j].x-p[k].x) + abs(p[j].y - p[k].y);
				graph[j][k] = len;
				graph[k][j] = len;
			}
		}
		
		
		if (bfs())
			cout << "happy" << endl;
		else
			cout << "sad" << endl;

		if(i!=T-1)
			clear();
	}

	return 0;
}