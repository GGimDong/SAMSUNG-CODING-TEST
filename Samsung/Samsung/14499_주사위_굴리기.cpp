#include <fstream>
#include <iostream>
#define MAX_N 20
#define MAX_K 1000

using namespace std;

int board[MAX_N][MAX_N];
int dice[6] = {1,2,3,4,5, 6};
int dice_idx = 1;
int N, M, x, y, K;
int ins[MAX_K]; // ������ 1, ������ 2, ������ 3, ������ 4

void rollong_dice(int k) {

}


// �ֻ����� ���� ������ ��������
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
	������ �� ĭ���� ������ �ϳ��� ������ �ִ�. 
	�ֻ����� ������ ��, �̵��� ĭ�� ���� �ִ� ���� 0�̸�, �ֻ����� �ٴڸ鿡 ���� �ִ� ���� ĭ�� ����ȴ�. 
	0�� �ƴ� ��쿡�� ĭ�� ���� �ִ� ���� �ֻ����� �ٴڸ����� ����Ǹ�, ĭ�� ���� �ִ� ���� 0�� �ȴ�.
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