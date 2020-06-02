#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#define MAX_N 20

using namespace std;

int N;
int board[MAX_N][MAX_N];
int area_board[MAX_N][MAX_N];
int ans = -1;

void print_baord() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << area_board[i][j];
		cout << endl;
	}
}

void clear_board() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			area_board[i][j] = 0;
	return;
}

void calc() {
	int score[6] = {0,0,0,0,0,0};
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			score[area_board[i][j]] += board[i][j];
	int max = score[1];
	int min = score[1];
	for (int i = 2; i < 6; i++){
		if (score[i] > max)
			max = score[i];
		if (score[i] < min)
			min = score[i];
	}
	int temp_ans = max - min;
	if (temp_ans < ans || ans == -1)
		ans = temp_ans;
	return;
}

void seperate_area(int r, int c, int d1, int d2) {
/*
	(x, y), (x+1, y-1), ..., (x+d1, y-d1)
	(x, y), (x+1, y+1), ..., (x+d2, y+d2)
	(x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
	(x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
*/
	//cout << r<<", " << c <<": "<< d1<<" " << d2 << endl;
	for (int i = 0; i <= d1; i++)
		area_board[r+i][c-i] = 5;
	for (int i = 0; i <= d2; i++)
		area_board[r+i][c+i] = 5;
	for (int i = 0; i <= d2; i++)
		area_board[r + d1 + i][c -d1 + i] = 5;
	for (int i = 0; i <= d1; i++)
		area_board[r + d2 + i][c + d2 - i] = 5;

	for (int i = 0; i < N; i++) {
		int first = -1;
		int second = -1;
		for (int j = 0; j < N; j++) {
			if (area_board[i][j] == 5) {
				if (first == -1)
					first = j;
				else
					second = j;
			}
			if (second != -1) {
				for (int ii = first; ii < second; ii++)
					area_board[i][ii] = 5;
				break;
			}
		}
	}
	//print_baord();
	//system("pause");

/*
	1번 선거구: 1 ≤ r < x+d1, 1 ≤ c ≤ y
	2번 선거구: 1 ≤ r ≤ x+d2, y < c ≤ N
	3번 선거구: x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
	4번 선거구: x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N
*/
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++){
			if (i < r + d1 && j <= c && area_board[i][j] == 0)
				area_board[i][j] = 1;
			else if (i <= r + d2 && c < j && area_board[i][j] == 0)
				area_board[i][j] = 2;
			else if (r+d1 <= i && j < c -d1 +d2 && area_board[i][j] == 0)
				area_board[i][j] = 3;
			else if (r + d2 < i && c - d1 + d2 <= j  && area_board[i][j] == 0)
				area_board[i][j] = 4;
		}

	//print_baord();
	//system("pause");
	calc();
	return;
}

void check_board(int r, int c) {
	
	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++) {
			if (r + i < N && c-i >=0 && r+j <N && c +j < N && r + i + j < N && c - i + j < N) {
				clear_board();
				seperate_area(r, c, i, j);
			}
		}

	return;
}


int main() {

	ifstream input;
	input.open("input/input.txt");

	input >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			input >> board[i][j];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			check_board(i,j);

	cout << ans;
	return 0;
}