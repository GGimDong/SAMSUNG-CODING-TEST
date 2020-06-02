#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAX 50

using namespace std;

int R, C, T;
int board[MAX][MAX];
int d_dust[MAX][MAX];
int ans = 0;
int air_pos[2][2]; // ����û������ ��ġ
/*����*/ void print_board(){for (int i = 0; i < R; i++) { for (int j = 0; j < C; j++) printf("%d\t",board[i][j]); cout << endl;}}

void cal_dust() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (board[i][j] > 0) ans += board[i][j];
	cout<< ans;
}

void clear_dust_board() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			d_dust[i][j] = 0;
	return;
}

void apply_dust() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			board[i][j] = d_dust[i][j];
	board[air_pos[0][0]][air_pos[0][1]] = -1;
	board[air_pos[1][0]][air_pos[1][1]] = -1;
	clear_dust_board();
}

/*
	(r, c)�� �ִ� �̼������� ������ �� �������� Ȯ��ȴ�.
	������ ���⿡ ����û���Ⱑ �ְų�, ĭ�� ������ �� �������δ� Ȯ���� �Ͼ�� �ʴ´�.
	Ȯ��Ǵ� ���� Ar,c/5�̰� �Ҽ����� ������.
	(r, c)�� ���� �̼������� ���� Ar,c - (Ar,c/5)��(Ȯ��� ������ ����) �̴�.
*/

void spread(int x, int y) {
	int spread_num = 0; // ���� ���̰ų� ����û����� ������ ����.
	int total_dust = board[x][y];
	int spread_dust = board[x][y] / 5;

	// �¿� ���� Ȯ��
	if (y > 0 && board[x][y - 1] != -1) {
		d_dust[x][y - 1] += spread_dust;
		spread_num++;
	}
	if (y < C - 1 && board[x][y + 1] != -1) { 
		d_dust[x][y + 1] += spread_dust;
		spread_num++; 
	}
	if (x > 0 && board[x - 1][y] != -1) {
		d_dust[x - 1][y] += spread_dust;
		spread_num++;
	}
	if (x < R - 1 && board[x + 1][y] != -1) {
		d_dust[x + 1][y] += spread_dust;
		spread_num++;
	}

	d_dust[x][y] += total_dust - spread_dust * spread_num;
	return;
}

void spread_dust() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (board[i][j] > 0)
				spread(i, j);
	apply_dust();
}

void generate_aircleaner() {
	// ���� ����
	int i = air_pos[0][0];
	int j = air_pos[0][1];
	while ( i > 0) {
		if(board[i][j] != -1)
			board[i][j] = board[i-1][j];
		i--;
	}
	j = 0;
	while (j < C-1) {
		board[0][j] = board[0][j + 1];
		j++;
	}

	i = 0;
	j = C-1;
	while (i < air_pos[0][0]) {
		board[i][j] = board[i+1][j];
		i++;
	}
	i = air_pos[0][0];
	j = C - 1;
	while (j > 0) {
		if (board[i][j-1] != -1)
			board[i][j] = board[i][j - 1];
		else
			board[i][j] = 0;
		j--;
	}

	// �Ʒ���
	i = air_pos[1][0]+1;
	j = air_pos[1][1];
	while (i < R-1) {
		board[i][j] = board[i + 1][j];
		i++;
	}
	i = R - 1;
	j = 0;
	while (j < C-1) {
		board[i][j] = board[i][j+1];
		j++;
	}
	i = R - 1;
	j = C - 1;
	while (i > air_pos[1][0]) {
		board[i][j] = board[i-1][j];
		i--;
	}
	i = air_pos[1][0];
	j = C - 1;
	while (j>0) {
		if (board[i][j-1] == -1)
			board[i][j] = 0;
		else
			board[i][j] = board[i][j - 1];
		j--;
	}

}

int main() {
	ifstream input;
	input.open("input/input.txt");

	input >> R >> C >> T;
	int temp;
	int t = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			input >> temp;  
			board[i][j] = temp;
			if (temp == -1) {
				air_pos[t][0] =i;
				air_pos[t][1] = j;
				t++;
			}
		}

	for (int i = 0; i < T; i++) {
		spread_dust();
		generate_aircleaner();
		/*����*///print_board();
	}
	
	cal_dust();
	return 0;
}