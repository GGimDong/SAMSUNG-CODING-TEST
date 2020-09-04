#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int dir[4][2] = { {0,1} , {0,-1}, {-1,0}, {1,0} }; // ╩С(0), го(1), аб(2), ©Л(3)
int arr[4001][4001];
int temp_arr[4001][4001];
int e[1001];
int d_arr[1001];
int T, ans, num, a, b, c, d;

void simulate() {
	bool is_empty = false;
	
}

int main() {
	scanf("%d",&T);
	for (int time = 1; time <= T; time++) {
		ans = 0;
		scanf("%d", &num);
		for (int i = 1; i <= num; i++) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			a = 2 * (a + 1000), b = 2 * (b + 1000);
			arr[a][b] = i;
			d_arr[i] = c, e[i] = d;
		}
		simulate();
		printf("#%d %d\n", time, ans);
	}
	return 0;
}