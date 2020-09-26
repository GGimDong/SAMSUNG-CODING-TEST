#include <iostream>
#include <vector>

using namespace std;

struct edge{
	int u, v, c;
};

int N, M;
// 인접 리스트로 나타낸 그래프
edge edge_list[100001];

edge make_edge(int u, int v, int c) {
	edge temp;
	temp.u = u, temp.v = v, temp.c = c;
	return temp;
}

/*디버깅용*/
void print_graph() {
	for (int i = 1; i <= N-1; i++) 
		cout << i << ": " << edge_list[i].u << " >> " << edge_list[i].v << "(" << edge_list[i].c << ")" << endl;
}

void find_max_cost(int u, int v) {
	int total_cost = 0;
	int node = u;
	
	while (node != v) {

	}

}


int main() {
	cin >> N;
	int u, v, c;
	
	for (int i = 1; i <= N - 1; i++) {
		cin >> u >> v >> c;
		edge_list[i] = make_edge(u, v, c);
	}

	//print_graph();

	cin >> M;
	int q, a, b;
	for (int i = 0; i < M; i++) {
		cin >> q >> a >> b;

		// 1 i c: i번 간선의 비용을 c로 바꾼다.
		if (q == 1) 
			edge_list[a].c = b;
		else 
			find_max_cost(a,b);
		
	}

	return 0;
}