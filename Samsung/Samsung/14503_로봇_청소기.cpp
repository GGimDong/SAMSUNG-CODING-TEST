#include <fstream>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#define MAX_NUM 50

using namespace std;

int board[MAX_NUM][MAX_NUM];
int X, Y;
int clean_num = 0;

void print_board() {
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++)
			cout << board[i][j];
		cout << endl;
	}
}

int left_turn_d(int d) {
	d = d - 1;
	if (d == -1) d = 3;
	return d;
}

/*
1. 현재 위치를 청소한다.
2. 현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
	a. 왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
	b. 왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
	c. 네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
	d. 네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
*/
void clean(int x, int y, int d) {

	// d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽
	if (board[x][y] == 0) {
		board[x][y] = 2;
		clean_num++;
	}

	//cout << x << ", " << y << endl; print_board(); system("pause");

	/* 2-c나 2-d의 case */
	if (board[x - 1][y] != 0 && board[x + 1][y] != 0 && board[x][y - 1] != 0 && board[x][y + 1] != 0) {
		switch (d) {
		case 0:
			if (board[x + 1][y] == 1)
				return;
			else
				clean(x + 1, y, d);
			break;
		case 1:
			if (board[x][y - 1] == 1)
				return;
			else
				clean(x, y - 1, d);
			break;
		case 2:
			if (board[x-1][y] == 1)
				return;
			else
				clean(x-1, y, d);
			break;
		case 3:
			if (board[x ][y+1] == 1)
				return;
			else
				clean(x , y + 1, d);
			break;
		}
		return;
	}

	int left_value = -1;
	int next_dir;
	switch (d) {
	case 0:
		left_value = board[x][y-1];
		break;
	case 1:
		left_value = board[x-1][y];
		break;
	case 2:
		left_value = board[x][y+1];
		break;
	case 3:
		left_value = board[x+1][y];
		break;
	}

	if (left_value == 0) {
		// 해당 자리가 청소가 가능한 것
		switch (d) {
		case 0:
			y--;
			break;
		case 1:
			x--;
			break;
		case 2:
			y++;
			break;
		case 3:
			x++;
			break;
		}
	}

	
	clean(x,y, left_turn_d(d));
}

int main() {
	ifstream input;
	input.open("input/input.txt");

	input >> X >> Y;

	int r, c, d;
	input >> r >> c >> d;

	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			input >> board[i][j];

	clean(r,c,d);
	cout << clean_num;
	return 0;
}