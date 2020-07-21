#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100;
const int INF = 99999999;

vector<int> graph[MAX];
vector<int> cost[MAX];

int n, m, s, e;
int Table[MAX];
int check[MAX];

int main() {
	cin >> n >> m >> s >> e;

	/*
		graph[1]: 2 6 8 9
		cost[1]	: 1 1 3 9
		1���� ����� node���� 2 6 8 9 �̰� �ش� ������ ����ġ�� 1 1 3 9 �̴�.
	*/
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		graph[a].push_back(b);
		graph[b].push_back(a);

		cost[a].push_back(c);
		cost[b].push_back(c);
	}


	return 0;
}