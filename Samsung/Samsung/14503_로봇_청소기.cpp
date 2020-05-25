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
1. ���� ��ġ�� û���Ѵ�.
2. ���� ��ġ���� ���� ������ �������� ���ʹ������ ���ʴ�� Ž���� �����Ѵ�.
	a. ���� ���⿡ ���� û������ ���� ������ �����Ѵٸ�, �� �������� ȸ���� ���� �� ĭ�� �����ϰ� 1������ �����Ѵ�.
	b. ���� ���⿡ û���� ������ ���ٸ�, �� �������� ȸ���ϰ� 2������ ���ư���.
	c. �� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���� ��쿡��, �ٶ󺸴� ������ ������ ä�� �� ĭ ������ �ϰ� 2������ ���ư���.
	d. �� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���̸鼭, ���� ������ ���̶� ������ �� �� ���� ��쿡�� �۵��� �����.
*/
void clean(int x, int y, int d) {

	// d�� 0�� ��쿡�� ������, 1�� ��쿡�� ������, 2�� ��쿡�� ������, 3�� ��쿡�� ����
	if (board[x][y] == 0) {
		board[x][y] = 2;
		clean_num++;
	}

	//cout << x << ", " << y << endl; print_board(); system("pause");

	/* 2-c�� 2-d�� case */
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
		// �ش� �ڸ��� û�Ұ� ������ ��
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