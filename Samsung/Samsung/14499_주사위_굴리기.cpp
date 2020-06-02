#include <fstream>
#include <iostream>
#define MAX_N 20
#define MAX_K 1000

using namespace std;

int board[MAX_N][MAX_N];
int N, M, x, y, K;
int ins[MAX_K]; // 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4

// 주사위가 맵의 밖으로 나가는지
bool is_possible(int k) {

	return false;
}

void operate(int k) {
	int ans;

	if(is_possible(k))
		cout << ans << endl;
	return;
}


int main() {
	ifstream input;
	input.open("input/input.txt");

	input >> N >> M >> x >> y >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			input >> board[i][j];

	for (int i = 0; i < K; i++)
		input >> ins[i];

	for (int i = 0; i < K; i++)
		operate(ins[i]);

	return 0;
}