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

	for (int i = 0; i < n; i++) Table[i] = INF;
	Table[s] = 0;
	
	for (int i = 0; i < n; i++) {
		int minValue = INF, minIndex = -1;

		for (int j = 0; j < n; j++) {
			if (!check[j] && minValue > Table[j]) {
				minValue = Table[j];
				minIndex = j;
			}
		}

		check[minIndex] = true;

		for (int j = 0; j < graph[minIndex].size(); j++) {
			int Node2 = graph[minIndex][j];
			int Cost2 = cost[minIndex][j];

			if (Table[Node2] > Table[minIndex] + Cost2) {
				Table[Node2] = Table[minIndex] + Cost2;
			}
		}
	}

	cout << Table[e];
	return 0;
}