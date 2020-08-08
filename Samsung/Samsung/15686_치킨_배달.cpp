#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int N, M;
int chickenNum = 0;
int arr[50][50], t_arr[50][50];	// 0은 빈 칸, 1은 집, 2는 치킨집, 집의 개수는 2N개를 넘지 않으며, 적어도 1개는 존재
bool visited[50][50];
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
int ans = 999999999;

struct point {
	int x, y;
	bool open;
}chicken[14]; // 1 ~ 13

point make_point(int a, int b) {
	point temp;
	temp.x = a, temp.y = b;
	return temp;
}

void simulate() {
	// open 배열을 보면 폐업할지 안할지에 대한 여부가 나타남.
	queue <point> q;
	memset(visited, 0, sizeof(visited));

	for (int i = 1; i <= chickenNum; i++) {
		if (chicken[i].open) {	// i 번째 치킨집은 문을 연 상태라면, 치킨 거리 구하기
			q.push(make_point(chicken[i].x,chicken[i].y));
			visited[chicken[i].x][chicken[i].y] = true;
			t_arr[chicken[i].x][chicken[i].y] = 0;
		}
	}

	while (!q.empty()) {
		point p = q.front();
		q.pop();
		int x = p.x, y = p.y, time = t_arr[x][y];
		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i][0], ny = y + dir[i][1];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N || visited[nx][ny]) continue;
			t_arr[nx][ny] = time + 1;
			visited[nx][ny] = true;
			q.push(make_point(nx, ny));
		}
	}
	int result = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (arr[i][j] == 1) result += t_arr[i][j];
	
	if (result < ans) ans = result;
}

void doRecursion(int current, int start, int target){
	if (current >= target) simulate();
	else 
		for (int i = start; i <= chickenNum; i++) {
			if (!chicken[i].open) {
				chicken[i].open = true;
				doRecursion(current + 1, i ,target);
				chicken[i].open = false;
			}
		}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) chicken[++chickenNum].x = i, chicken[chickenNum].y = j;
		}

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= chickenNum; j++) chicken[j].open = false;	// 초기화
		doRecursion(0, 1, i);
	}

	cout << ans;
	return 0;
}