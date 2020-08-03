#include <iostream>

using namespace std;

int N, M, r, c, K;
int arr[20][20], order[1000];
int dice[7] = { 0, 1, 2, 3, 4, 5, 6};
int t_dice[7];
int diceValue[7] = { 0, };

//  동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4
int dir[5][2] = { {0,0},{0,1},{0,-1},{-1,0},{1,0} };
int moveArr[5][7] = {
	{0, 0, 0, 0, 0, 0, 0},
	{0, 3, 2, 6, 1, 5, 4},
	{0, 4, 2, 1, 6, 5, 3},
	{0, 2, 6, 3, 4, 1, 5},
	{0, 5, 1, 3, 4, 6, 2}
};

void move(int d) {
	int nr = r + dir[d][0], nc = c + dir[d][1];
	if (nr < 0 || nc < 0 || nr >= N || nc >= M) return;	// 지도 밖 나가면 실행 X
	// 업데이트
	r = nr, c = nc;
	for (int i = 1; i <= 6; i++) t_dice[i] = dice[moveArr[d][i]];
	for (int i = 1; i <= 6; i++) dice[i] = t_dice[i];

	if (arr[r][c] == 0) {
		arr[r][c] = diceValue[dice[1]];
	}
	else {
		diceValue[dice[1]] = arr[r][c];
		arr[r][c] = 0;
	}
	cout << diceValue[dice[6]] << endl;
}

int main() {
	cin >> N >> M >> r >> c >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> arr[i][j];

	for (int i = 0; i < K; i++) cin >> order[i];
	
	for (int i = 0; i < K; i++) move(order[i]);

	return 0;
}