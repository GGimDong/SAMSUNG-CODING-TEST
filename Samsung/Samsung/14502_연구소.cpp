#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#define MAX_NUM 8

using namespace std;

int board[MAX_NUM][MAX_NUM];
int x, y;
int max_value = -1; 

void print_board() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			cout << board[i][j]<<" ";
		cout << endl;
	}
}


struct point {
	int x;
	int y;
};

void spread_virus(int board[MAX_NUM][MAX_NUM], int i, int j) {
	vector<point> v;
	point init;
	init.x = i;
	init.y = j;
	v.push_back(init);

	do {
		point new_point;
		point temp_p = v.back();
		v.pop_back();
		
		if (temp_p.y + 1 < y && board[temp_p.x][temp_p.y + 1] == 0) {
			board[temp_p.x][temp_p.y + 1] = 2;
			new_point.x = temp_p.x;
			new_point.y = temp_p.y +1;
			v.push_back(new_point);
		}

		if (temp_p.y > 0 && board[temp_p.x][temp_p.y - 1] == 0) {
			board[temp_p.x][temp_p.y - 1] = 2;
			new_point.x = temp_p.x;
			new_point.y = temp_p.y - 1;
			v.push_back(new_point);
		}

		if (temp_p.x + 1 < x && board[temp_p.x + 1][temp_p.y] == 0) {
			board[temp_p.x + 1][temp_p.y] = 2;
			new_point.x = temp_p.x + 1;
			new_point.y = temp_p.y;
			v.push_back(new_point);
		}

		if (temp_p.x > 0 && board[temp_p.x - 1][temp_p.y] == 0) {
			board[temp_p.x - 1][temp_p.y] = 2;
			new_point.x = temp_p.x - 1;
			new_point.y = temp_p.y;
			v.push_back(new_point);
		}
		
		//cout << i + 1 << ", " << j + 1 << " >> " << endl;
		//print_board();
		//system("pause");

	} while (!v.empty());

	
}

void calc() {
	int temp_board[MAX_NUM][MAX_NUM];
	int temp_max = 0;

	for (int i = 0; i < x; i++) 
		for (int j = 0; j < y; j++)
			temp_board[i][j] = board[i][j];
				
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			if (temp_board[i][j] == 2)
				spread_virus(temp_board, i ,j);

	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			if (temp_board[i][j] == 0)
				temp_max++;

	if (max_value == -1 || max_value < temp_max)
		max_value = temp_max;

	return;
}

void virus_attack(int i, int j, int n) {
	
	if (n == 3) {
		calc();
		return;
	}
	
	if (i == x && j== 0) return;

	if (board[i][j] != 0) {
		/* 벽이나 바이러스가 존재하는 경우 */
		if (j + 1 < y ) 
			virus_attack(i, j + 1, n);
		else 
			virus_attack(i + 1, 0, n);
	}
	else {
		/* 빈 곳인 경우 */
		if (j + 1 < y) {
			/* 놓고 지나가는 경우 */
			board[i][j] = 1;
			virus_attack(i, j + 1, n+1);
			board[i][j] = 0;

			/* 안 놓고 지나가는 경우 */
			virus_attack(i, j + 1, n);
		}
		else {
			/* 놓고 지나가는 경우 */
			board[i][j] = 1;
			virus_attack(i + 1, 0, n+1);
			board[i][j] = 0;
			
			/* 안 놓고 지나가는 경우 */
			virus_attack(i + 1, 0, n);
		}
	}

	return;
}

int main() {
	ifstream input;
	input.open("input/input.txt");
	input >> x >> y;

	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			input >> board[i][j];
	
	virus_attack(0,0,0);
	cout << max_value;

	return 0;
}