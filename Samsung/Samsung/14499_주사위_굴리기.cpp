#include <fstream>
#include <iostream>
#define MAX_N 20
#define MAX_K 1000

using namespace std;

int board[MAX_N][MAX_N];
int dice[6] = {1,2,3,4,5, 6};
int dice_idx = 1;
int N, M, x, y, K;
int ins[MAX_K]; // 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4

void rollong_dice(int k) {

}


// 주사위가 맵의 밖으로 나가는지
bool is_possible(int k) {
	switch (k) {
	case 1:
		if (y + 1 == M)	return false;
		else return true;
	case 2:
		if (y == 0)	return false;
		else return true;
	case 3:
		if (x == 0)	return false;
		else return true;
	case 4:
		if ( x+1  == N)	return false;
		else return true;
	}
}

/*
	지도의 각 칸에는 정수가 하나씩 쓰여져 있다. 
	주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다. 
	0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.
*/
void operate(int k) {
	int ans;

	if (is_possible(k)) {
		cout << ans << endl;
	}
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