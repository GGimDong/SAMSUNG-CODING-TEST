#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct pos {
	int x;
	int y;
};

pos init_R, init_B, hole;
int N, M;
int min_result = -1;

/*	Board의 구성요소
	0: 빈 곳
	1: 벽
	2: 구멍
	3: Red
	4: Blue
*/
int board[10][10];

// pos의 값들을 저장하기
pos R[10][4];
pos B[10][4];

/*지워*/void print_board() { for (int i = 0; i < N; i++) { for (int j = 0; j < M; j++) if (board[i][j] == 1)cout << "#"; else if (board[i][j] == 0) cout << " " ; else if (board[i][j] == 2) cout << "O"; else cout << board[i][j]; cout << endl; } }

/* 기존의 R, B를 지우고 새로운 R, B를 보드에 넣음 */
void set_R_B(pos R, pos B) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] == 3 || board[i][j] == 4)
				board[i][j] = 0;

	board[R.x][R.y] = 3;
	board[B.x][B.y] = 4;

	return;
}

// 그 이전 값의 R과 B로 update
void set_last_R_B() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j] == 3 || board[i][j] == 4)
				board[i][j] = 0;

	board[init_R.x][init_R.y] = 3;
	board[init_B.x][init_B.y] = 4;

	return;
}

/*	1, 2의 경우 상단 위에서 돌리고 3, 4는 하단 아래에서 돌림.
	>> op의 명령 종류
	1: 상 
	2: 좌 
	3: 하 
	4: 우
	>> n은 타임에 대한 idx로 9가 max
*/
void move(int op) {
	cout << "Op: " << op << endl;
	int temp_i, temp_j;
	if (op == 1 || op == 2) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (board[i][j] == 3 || board[i][j] == 4) {
					temp_i = i;
					temp_j = j;
					if (op == 1) {
						/*지워*/cout << "Up" << endl;
						while (board[temp_i - 1][temp_j] == 2 || board[temp_i - 1][temp_j] == 0) {
							if (board[temp_i - 1][temp_j] == 0) {
								board[temp_i - 1][temp_j] = board[temp_i][temp_j];
								board[temp_i][temp_j] = 0;
							}
							else if (board[temp_i - 1][temp_j] == 2) {
								board[temp_i][temp_j] = 0;
								break;
							}
							temp_i--;
							//temp_j--;
						}
					}
					else {
						/*지워*/cout << "Left" << endl;
						while (board[temp_i][temp_j - 1] == 2 || board[temp_i][temp_j - 1] == 0) {
							if (board[temp_i][temp_j - 1] == 0) {
								board[temp_i][temp_j - 1] = board[temp_i][temp_j];
								board[temp_i][temp_j] = 0;
							}
							else if (board[temp_i][temp_j - 1] == 2) {
								board[temp_i][temp_j] = 0;
								break;
							}
							//temp_i--;
							temp_j--;
						}
					}
				}
	}
	else {
		for (int i = N - 1; i >= 0; i--)
			for (int j = M - 1; j >= 0; j--)
				if (board[i][j] == 3 || board[i][j] == 4) {
					temp_i = i;
					temp_j = j;
					if (op == 3) {
						/*지워*/cout << "Down" << endl;
						while (board[temp_i + 1][temp_j] == 2 || board[temp_i + 1][temp_j] == 0) {
							if (board[temp_i + 1][temp_j] == 0) {
								board[temp_i + 1][temp_j] = board[temp_i][temp_j];
								board[temp_i][temp_j] = 0;
							}
							else if (board[temp_i + 1][temp_j] == 2) {
								board[temp_i][temp_j] = 0;
								break;
							}
							temp_i++;
							//temp_j--;
						}
					}
					else {
						/*지워*/cout << "Right" << endl;
						while (board[temp_i][temp_j + 1] == 2 || board[temp_i][temp_j + 1] == 0) {
							if (board[temp_i][temp_j + 1] == 0) {
								board[temp_i][temp_j + 1] = board[temp_i][temp_j];
								board[temp_i][temp_j] = 0;
							}
							else if (board[temp_i][temp_j + 1] == 2) {
								board[temp_i][temp_j] = 0;
								break;
							}
							//temp_i--;
							temp_j++;
						}
					}
				}
	}

	/*지워*/ print_board(); system("pause");

	return;
}


void BFS(pos R, pos B, int n) {
	if(n == 10)
		return;

	move(3);
	set_last_R_B();

	move(1);
	set_last_R_B();

	move(2);
	set_last_R_B();

	move(4);
	set_last_R_B();

}

int main() {
	ifstream input;
	input.open("input/input.txt");
	char temp;

	// initialize
	input >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++){
			input >> temp;
			if (temp == '#') 
				board[i][j] = 1;
			else if(temp == '.')
				board[i][j] = 0;
			else if (temp == 'R') {
				board[i][j] = 3;
				init_R.x = i;
				init_R.y = j;
			}
			else if (temp == 'B') {
				board[i][j] = 4;
				init_B.x = i;
				init_B.y = j;
			}
			else if (temp == 'O') {
				board[i][j] = 2;
				hole.x = i;
				hole.y = j;
			}
		}
	
	/*지워*/cout << "INIT: " << endl; print_board();
	

	BFS(init_R, init_B, 0);

	cout << min_result;
	return 0;
}