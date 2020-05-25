#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#define MAX_SIZE 12

using namespace std;
int edge=0;
int width = 0;
int ans = 12 * 12;
int total_P = 0;
int max_P = 0;


void init() {
	width = 0;
	edge = 0;
	total_P = 0;
	ans = 12*12;
	max_P = 0;
}

// 아래 x, 오른쪽 y
void dfs(vector<int> x, vector<int> y, int processed_process,int board[MAX_SIZE][MAX_SIZE],int P, int line) {
	if (processed_process == total_P) {
		if (max_P < P) {
			max_P = P;
			ans = line;
			
		}
		else if (max_P == P && ans > line) {
			ans = line;
		}

		return;
	}

	int board_change[MAX_SIZE][MAX_SIZE];
	for (int ii = 0; ii < width; ii++)
		for (int jj = 0; jj < width; jj++)
			board_change[ii][jj] = board[ii][jj];

	// 계산할 P가 없으니 끝내면 됨!
	int P_x, P_y;
	
	P_x = x[processed_process];
	P_y = y[processed_process];
	
	// 가장자리의 P일 경우 그냥 연결하고 PASS
	if (P_x == 0 || P_x == width - 1 || P_y == 0 || P_y == width - 1) {
		// 그럼 cost없이 상승하므로 그냥 ans를 max값으로 넣어준다!
		dfs(x, y, processed_process+1, board,P+1, line);
	}
	else { // 가장자리가 아닌 경우
		
		/***** 왼쪽으로 주욱 ****/ 
		int check_left = 0;
		for (int i = 0; i < P_x; i++) {
			if (board[i][P_y] != 0){
				check_left = 1;
				break;
			}
		}
		//왼쪽 OK 진행
		if (check_left == 0) {

			for (int ii = 0; ii < width; ii++)
				for (int jj = 0; jj < width; jj++)
					board_change[ii][jj] = board[ii][jj];

			edge = 0;
			for (int i = 0; i < P_x; i++) {
				board_change[i][P_y] = 2;
				edge++;
			}

			dfs(x, y, processed_process + 1, board_change, P + 1, line + edge);
		}
		/***************************/

		/***** 오른쪽으로 주욱 ****/
		int check_right = 0;
		for (int i = P_x+1; i < width; i++) {
			if (board[i][P_y] != 0) {
				check_right = 1;
				break;
			}
		}
		//오른쪽 OK 진행
		if (check_right == 0) {

			for (int ii = 0; ii < width; ii++)
				for (int jj = 0; jj < width; jj++)
					board_change[ii][jj] = board[ii][jj];

			edge = 0;
			for (int i = P_x + 1; i < width; i++) {
				board_change[i][P_y] = 2;
				edge++;
			}
			dfs(x, y, processed_process + 1, board_change, P + 1, line + edge);
		}
		/***************************/
		

		/***** 위쪽으로 주욱 ****/
		int check_up = 0;
		for (int i = 0 ; i < P_y; i++) {
			if (board[P_x][i] != 0) {
				check_up = 1;
				break;
			}
		}
		//위쪽 OK 진행
		if (check_up == 0) {

			for (int ii = 0; ii < width; ii++)
				for (int jj = 0; jj < width; jj++)
					board_change[ii][jj] = board[ii][jj];

			edge = 0;
			for (int i = 0; i < P_y; i++) {
				board_change[P_x][i] = 2;
				edge++;
			}
			dfs(x, y, processed_process + 1, board_change, P + 1, line + edge);
		}
		/***************************/
		
		/***** 아래쪽으로 주욱 ****/
		int check_down = 0;
		for (int i = P_y+1; i < width; i++) {
			if (board[P_x][i] != 0) {
				check_down = 1;
				break;
			}
		}
		// 아래쪽 OK 진행
		if (check_down == 0) {

			for (int ii = 0; ii < width; ii++)
				for (int jj = 0; jj < width; jj++)
					board_change[ii][jj] = board[ii][jj];



			edge = 0;
			for (int i = P_y + 1; i < width; i++) {
				board_change[P_x][i] = 2;
				edge++;
			}
			dfs(x, y, processed_process + 1, board_change, P + 1, line + edge);
		}
		/***************************/

		// Skip 하고 넘어가보기
		dfs(x, y, processed_process + 1, board,P, line);
		

	}


}

int main() {
	ifstream input;
	input.open("input.txt");
	
	vector<int> x_pos;
	vector<int> y_pos;

	int iteration;
	input >> iteration;

	int board[MAX_SIZE][MAX_SIZE];

	for (int i = 0; i < iteration; i++) {
		input >> width;
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < width; k++) {
				input >> board[j][k];
				
				if (board[j][k] == 1) {
					x_pos.push_back(j);
					y_pos.push_back(k);
					total_P++;
				}
			}
		}

		dfs(x_pos,y_pos, 0, board,0, 0);

		printf("#%d %d\n", i+1, ans);
		x_pos.clear();
		y_pos.clear();
		init();
	}

	input.close();
	return 0;
}
/*

3
7
0 0 1 0 0 0 0
0 0 1 0 0 0 0
0 0 0 0 0 1 0
0 0 0 0 0 0 0
1 1 0 1 0 0 0
0 1 0 0 0 0 0
0 0 0 0 0 0 0
9
0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0
0 0 0 1 0 0 0 0 0
0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1
11
0 0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1
0 0 0 1 0 0 0 0 1 0 0
0 1 0 1 1 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
*/