#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int dir[4][2] = { {0,1} , {0,-1}, {-1,0}, {1,0} }; // ��(0), ��(1), ��(2), ��(3)
int arr[5000][5000];
int T, ans, num, a, b, c, d;

int main() {
	scanf("%d",&T);
	for (int time = 1; time <= T; time++) {
		
		printf("#%d %d\n",time, ans);
	}
	return 0;
}