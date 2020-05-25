#include <cstdio>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>

using namespace std;

int board[10][10];

// ���� �׷���
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
	if (a.length < b.length) return true; // ���� ���� f�� �������� �������� ����
	return false;
}

/* Kruskal algorithm���� cycle�� Ž���� Union-FInd �Լ� */
// x ����� root�� ã���ְ� parent�� ������Ʈ
int Find(int x, int * parent) {
	if (x == parent[x])
		return x;
	else {
		int p = Find(parent[x], parent);
		parent[x] = p;
		return p;
	}
}

// x ���� y ��带 ����, �����ϸ� cycle�� ����
void Union(int x, int y, int * parent) {
	x = Find(x, parent);
	y = Find(y, parent);

	// ���Ⱑ cycle �Ǵ� ����
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
	
	/*����*/printf("Before:\n"); for (int i = 0; i < q.size(); i++) { printf("%d >> %d: %d\n", q[i].start, q[i].target, q[i].length); }cout << endl;
	sort(q.begin(), q.end(), cmp);

	/* WARNING: ���⼭���� �ٽ� �ڵ��ؾ� ��! */
	/*����*/printf("After:\n"); for (int i = 0; i < q.size(); i++) { printf("%d >> %d: %d\n", q[i].start, q[i].target, q[i].length); }cout << endl;
	
	int result = 0;
	
	vector<v> q_for_mst;

	/* TODO: ������ �� queue�� �޾Ƽ� kruskal �˰����� ���� �ִ� ��� Ʈ�� ���� */
	while (q.size() != 0) {
		
		// ���� max�� 6�̴ϱ�
		v temp = q.front();
		q.erase(q.begin());
		if (is_cycle(q_for_mst, temp.start, temp.target)) {
			/*����*/ cout << "Connet: " << temp.start << " >> " << temp.target << ": " << temp.length << endl;
			q_for_mst.push_back(temp);
			result += temp.length;
		}
		
	}

	/* TODO: Kruskal �˰����� ����� ���*/
	printf("%d", result);
}

/* ������ ��� ������ ������ ���� ���� üũ */
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
		Left check, ���� ���ʿ� üũ�� ���� �ְ� ������ �־�� �ϰ� �Ȱ��� ���� ������ Ż��
		���ʸ� üũ�ϸ� �������� �ڵ����� üũ�� ��!
	*/
	if (j > 1 && board[i][j - 1] != start_island) {
		for (int ii = j - 1; ii >= 0; ii--)
			if (board[i][ii] != 0) {
				int target_island = board[i][ii];
				int length = positive(ii-j)-1;
				
				if (length < 2) break;
				
				/*����*/ printf("�¿� (%d,%d) ~ (%d,%d) : %d \n", i + 1, ii + 1, i + 1, j + 1, length);

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

				/*����*/ printf("���� (%d,%d) ~ (%d,%d) : %d \n", ii + 1, j + 1, i + 1, j + 1, length);

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
				// ���� ã�Ҵ�!
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

	/*����*/print_board();

	update_graph();
	
	/*����*/print_graph();

	if (connection_check()) {
		Kruskal();
	}
	else {
		printf("-1");
	}
	
	return 0;
}