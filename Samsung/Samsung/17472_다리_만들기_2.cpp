#include <cstdio>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>

using namespace std;

int board[10][10];

// 섬의 그래프
int graph[7][7];

int N, M;
int island_num = 1;

void print_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			printf("%d ", board[i][j]);
		printf("\n");
	}printf("\n");
}

void print_graph() {
	for (int i = 1; i < island_num; i++) {
		for (int j = 1; j < island_num; j++)
			printf("%d ", graph[i][j]);
		printf("\n");
	}printf("\n");
}

int positive(int n ) {
	if (n < 0)
		return -1*n;

	return n;
}

struct v{
	int length;
	int start;
	int target;
};

bool cmp(const v & a, const v & b)
{
	if (a.length < b.length) return true; // 제일 먼저 f를 기준으로 오름차순 정렬
	return false;
}

/* Kruskal algorithm에서 cycle을 탐지할 Union-FInd 함수 */
// x 노드의 root를 찾아주고 parent를 업데이트
int Find(int x, int * parent) {
	if (x == parent[x])
		return x;
	else {
		int p = Find(parent[x], parent);
		parent[x] = p;
		return p;
	}
}

// x 노드와 y 노드를 연결, 동일하면 cycle이 생김
void Union(int x, int y, int * parent) {
	x = Find(x, parent);
	y = Find(y, parent);

	// 여기가 cycle 판단 지역
	if (x != y) {
		parent[y] = x;
	}
}

int is_cycle(vector<v> q, int a, int b) {
	if (q.empty())
		return 1;
	
	int parent[7] = { 0,1,2,3,4,5,6 };
	
	do {
		v temp = q.front();
		q.erase(q.begin());

		Union(temp.start, temp.target,parent);

	} while (!q.empty());
	
	if (Find(a, parent) == Find(b, parent))
		return 0;
	else
		return 1;
}

void Kruskal() {
	vector<v> q;
	vector<v> q_c;

	for (int i = 1; i < island_num;i++) 
		for (int j = i+1; j < island_num; j++)
			if (graph[i][j] != 0) {
				v new_vertex;
				new_vertex.start = i;
				new_vertex.target = j;
				new_vertex.length = graph[i][j];
				q.push_back(new_vertex);
			}
	
	/*지워*/printf("Before:\n"); for (int i = 0; i < q.size(); i++) { printf("%d >> %d: %d\n", q[i].start, q[i].target, q[i].length); }cout << endl;
	sort(q.begin(), q.end(), cmp);

	/* WARNING: 여기서부터 다시 코딩해야 함! */
	/*지워*/printf("After:\n"); for (int i = 0; i < q.size(); i++) { printf("%d >> %d: %d\n", q[i].start, q[i].target, q[i].length); }cout << endl;
	
	int result = 0;
	
	vector<v> q_for_mst;

	/* TODO: 정렬이 된 queue를 받아서 kruskal 알고리즘을 통해 최단 경로 트리 구성 */
	while (q.size() != 0) {
		
		// 섬의 max가 6이니까
		v temp = q.front();
		q.erase(q.begin());
		if (is_cycle(q_for_mst, temp.start, temp.target)) {
			/*지워*/ cout << "Connet: " << temp.start << " >> " << temp.target << ": " << temp.length << endl;
			q_for_mst.push_back(temp);
			result += temp.length;
		}
		
	}

	/* TODO: Kruskal 알고리즘의 결과를 출력*/
	printf("%d", result);
}

/* 섬들이 모두 연결이 가능한 지에 대한 체크 */
bool connection_check() {
	queue<int> q;
	int is_check[7] = {0,1,0,0,0,0,0};
	q.push(1);

	do {
		int temp = q.front();
		q.pop();
		for(int i =1;i<island_num;i++)
			if (graph[temp][i] != 0 && is_check[i] == 0) {
				q.push(i);
				is_check[i]=1;
			}
	} while (!q.empty());

	for (int i = 1; i < island_num; i++) {
		if (is_check[i] == 0)
			return false;
	}
	return true;
}

void find_another_island(int i, int j) {
	int start_island = board[i][j];
	/*
		Left check, 먼저 왼쪽에 체크할 섬이 있게 공간이 있어야 하고 똑같은 섬이 있으면 탈락
		왼쪽만 체크하면 오른쪽은 자동으로 체크가 됨!
	*/
	if (j > 1 && board[i][j - 1] != start_island) {
		for (int ii = j - 1; ii >= 0; ii--)
			if (board[i][ii] != 0) {
				int target_island = board[i][ii];
				int length = positive(ii-j)-1;
				
				if (length < 2) break;
				
				/*지워*/ printf("좌우 (%d,%d) ~ (%d,%d) : %d \n", i + 1, ii + 1, i + 1, j + 1, length);

				if (length < graph[start_island][target_island] || graph[start_island][target_island] == 0) {
					graph[start_island][target_island] = length;
					graph[target_island][start_island] = length;
				}
				break;
			}
	}
	
	// Upside
	if (i >= 1 && board[i-1][j] != start_island) {
		for (int ii = i - 1; ii >= 0; ii--)
			if (board[ii][j] != 0) {
				int target_island = board[ii][j];
				int length = positive(ii - i) - 1;

				if (length < 2) break;

				/*지워*/ printf("상하 (%d,%d) ~ (%d,%d) : %d \n", ii + 1, j + 1, i + 1, j + 1, length);

				if (length < graph[start_island][target_island] || graph[start_island][target_island] == 0) {
					graph[start_island][target_island] = length;
					graph[target_island][start_island] = length;
				}
				break;
			}
	}

}

void update_graph() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] != 0) {
				// 섬을 찾았다!
				find_another_island(i,j);
			}

}

void check(int i, int j) {
	board[i][j] = island_num;
	if (i + 1 < N)
		if (board[i + 1][j] == -1)
			check(i + 1, j);
	if (i - 1 >= 0)
		if (board[i - 1][j] == -1)
			check(i - 1, j);
	if (j + 1 < M)
		if (board[i][j + 1] == -1)
			check(i, j + 1);
	if (j - 1 >= 0)
		if (board[i][j - 1] == -1)
			check(i, j - 1);
}

void island_check() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] == -1) {
				check(i, j);
				island_num++;
			}
}

int main() {
	ifstream input;
	input.open("input/input.txt");

	input >> N;
	input >> M;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			int a; 
			input >> a;
			if (a == 1)
				board[i][j] = -1;
			else
				board[i][j] = 0;
		}

	island_check();

	/*지워*/print_board();

	update_graph();
	
	/*지워*/print_graph();

	if (connection_check()) {
		Kruskal();
	}
	else {
		printf("-1");
	}
	
	return 0;
}