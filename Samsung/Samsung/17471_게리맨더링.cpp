#include <cstdio>
#include <fstream>
#include <stack>
#include <vector>
#define MAX_N 11

using namespace std;

// node 수, edge 수, 
int N, e;
int graph[MAX_N][MAX_N];
int people[MAX_N];

int total_num, num_1, num_2;
int ans = 99999;
int group[MAX_N] = {};//{0,1,1,1,1,1,1,1,1,1,1};

int positive(int n) {
	if (n < 0)
		n = -1 * n;
	return n;
}


void print_group() {
	for (int i = 1; i <= N; i++)
		printf("%d ", group[i]);
	printf("\n");
}

int check_group(vector<int> vec) {
	/* vec.size() 까지의 값이 전부 1로 check되면 결과 트루 */
	int is_visited[MAX_N] = { 1,1,1,1,1,1,1,1,1,1,1 };

	for (int i = 0; i < vec.size(); i++)
		is_visited[vec[i]] = 0;

	stack<int> stack_dfs;

	stack_dfs.push(vec[0]);
	is_visited[vec[0]] = 1;

	do {
		/* TODO: DFS를 통해 탐색 구현 */
		int temp = stack_dfs.top();
		stack_dfs.pop();
		
		for (int i = 1; i <= N; i++) {
			if (graph[temp][i] == 1 && is_visited[i] == 0) {
				stack_dfs.push(i);
				is_visited[i] = 1;
			}
		}
	} while (stack_dfs.size()!=0);


	/*printf("is_visted: ");
	for (int i = 1; i <= N; i++)
		printf("%d ", is_visited[i]);
	printf("\n");*/


	for(int i=1;i<=N;i++)
		if(is_visited[i]==0)
			return 0;
	return 1;
}

void group_comb(int n) {
	if(n==N+1){
		
		/* 여기서 dfs로 두 그룹이 다 연결이 되어 있는지를 확인해야함. */
		int is_possible = 0;

		vector<int> vec_1;
		vector<int> vec_2;
		for (int i = 1; i <= N; i++) {
			if (group[i] == 1)
				vec_1.push_back(i);
			else
				vec_2.push_back(i);
		}

		/* 전부 동일 그룹일 경우는 예외로 없애버림 */
		if (vec_1.size() == 0 || vec_2.size() == 0)
			return;
		
		/*지워*///print_group();

		/* check 의 결과들이 전부 dfs가 잘 되었는지를 확인해야 함! */
		if (check_group(vec_1) == 1 && check_group(vec_2) == 1)
			is_possible = 1;

		/* 연결이 되어 있을 경우, 값을 출력하게 함. */
		if (is_possible == 1) {
			/*지워*/ //printf("Can divide! \n");
			num_1 = 0;
			num_2 = 0;
			for (int i = 1; i <= N; i++) {
				if (group[i] == 1)
					num_1 += people[i];
				else
					num_2 += people[i];
			}
			int result = positive(num_1 - num_2);
			if (ans > result)
				ans = result;
		}
		return;
	}
	group[n] = 1;
	group_comb(n + 1);
	group[n] = 2;
	group_comb(n + 1);
}

int main() {
	
	// input:  1 2  3 4 
	// output: 1 0 -1 9
	ifstream input;
	input.open("input/Gary/input4.txt");

	input >> N;
	for (int i = 1; i <= N; i++) {
		input >> people[i];
		total_num += people[i];
	}
	
	for (int i = 1; i <= N; i++) {
		// edge 수
		input >> e;
		for (int j = 0; j < e; j++) {
			int temp;
			input >> temp;			
			graph[i][temp] = 1;
			graph[temp][i] = 1;
		}
	}
	//printf("Total_num: %d \n", total_num);

	group_comb(1);
	if (ans == 99999)
		printf("-1");
	else
		printf("%d", ans);

	return 0;
}