#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N, M, V;
int arr[50][50]; 
bool order[10];
vector<pair<int, int> > v;
int ans = -1;
bool visited[50][50];
int time[50][50];
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };

void simulation() {
	memset(visited, 0, sizeof(visited)), memset(time, 0, sizeof(time));

	queue<pair<int, int> > q;
	for (int i = 0; i < v.size(); i++) 
		if (order[i]) {
			q.push(v[i]);
			visited[v[i].first][v[i].second] = true;
		}
	
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		int t = time[p.first][p.second];

		for (int i = 0; i < 4; i++) {
			int nx = p.first + dir[i][0], ny = p.second + dir[i][1];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N || visited[nx][ny] || arr[nx][ny] == 1) continue;
			time[nx][ny] = t + 1;
			visited[nx][ny] = true;
			q.push(make_pair(nx, ny));
		}
	}

	for (int i = 0; i < v.size(); i++) time[v[i].first][v[i].second] = 0;

	int max_t = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (!visited[i][j] && arr[i][j] != 1) return;
			if (time[i][j] > max_t) max_t = time[i][j];
		}

	if (ans == -1 || ans > max_t) ans = max_t;
}

void doRecursion(int current, int idx) {
	if (current >= M) {
		simulation();
	}
	else {
		for (int i = idx; i < v.size(); i++) {
			if (order[i] == false) {
				order[i] = true;
				doRecursion(current + 1, i);
				order[i] = false;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {
				v.push_back(make_pair(i,j));
			}
		}

	doRecursion(0, 0);

	cout << ans;
	return 0;
}